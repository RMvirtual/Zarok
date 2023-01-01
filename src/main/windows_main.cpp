#include <windows.h>

struct WindowValues
{
  DWORD behaviours;
  LPCWSTR className;
  LPCWSTR titleBar;
  DWORD style;
  int x;
  int y;
  int width;
  int height;
  HWND parentWindow;
  HMENU menu;
  HINSTANCE instanceHandle;
  LPVOID arbitraryData;
};

LRESULT CALLBACK updateCallback(
  HWND windowHandle, UINT updateEvent, WPARAM wParam, LPARAM lParam)
{
  switch (updateEvent) {
    case WM_DESTROY: {
      PostQuitMessage(0);
    } return 0;

    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(windowHandle, &ps);

      // All painting occurs here, between BeginPaint and EndPaint.
      FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
      EndPaint(windowHandle, &ps);
    } return 0;
  }

  return DefWindowProcW(windowHandle, updateEvent, wParam, lParam);
}

WNDCLASSW createWindowClass(HINSTANCE* instanceHandle)
{
  WNDCLASSW windowClass {};
  windowClass.lpfnWndProc = updateCallback;
  windowClass.hInstance = *instanceHandle;
  windowClass.lpszClassName = L"Fortesque";

  return windowClass;
}

void registerWindowClass(HINSTANCE* instanceHandle)
{
  const wchar_t windowClassName[] = L"Fortesque";

  WNDCLASSW windowClass = createWindowClass(instanceHandle);
  RegisterClassW(&windowClass);
}

HWND createWindow(HINSTANCE* instanceHandle)
{
  registerWindowClass(instanceHandle);

  return CreateWindowExW(
    0,
    L"Fortesque",                // Window class
    L"Fortesque",                // Window text
    WS_OVERLAPPEDWINDOW,         // Window style
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

    NULL,                         
    NULL,                         // Menu
    *instanceHandle,               // Instance handle
    NULL                          // Additional application data
  );
}

void runEventLoop()
{
  MSG event = {};

  while (GetMessageW(&event, NULL, 0, 0) > 0) {
    TranslateMessage(&event);
    DispatchMessageW(&event);
  }
}

/**
 * @brief Main entry point for the Windows API to launch from.
 */
int CALLBACK WinMain(
    HINSTANCE instanceHandle, HINSTANCE prevInstance,
    LPSTR commandLineArgs, int minimisationOption)
{
  auto windowHandle = createWindow(&instanceHandle);

  if (windowHandle == NULL)
    return 0;

  ShowWindow(windowHandle, minimisationOption);
  runEventLoop();

  return 0;
}
