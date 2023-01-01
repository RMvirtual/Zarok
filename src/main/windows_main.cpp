#include <string>
#include <windows.h>

struct WindowValues
{
  DWORD behaviours;
  std::wstring className;
  std::wstring titleBar;
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
  windowClass.lpszClassName = L"Zarok";

  return windowClass;
}

void registerWindowClass(HINSTANCE* instanceHandle)
{
  WNDCLASSW windowClass = createWindowClass(instanceHandle);
  RegisterClassW(&windowClass);
}

WindowValues mainWindowValues(HINSTANCE* instanceHandle)
{
  WindowValues result {};
  result.behaviours = 0;
  result.className = L"Zarok";
  result.titleBar = L"Zarok";
  result.style = WS_OVERLAPPEDWINDOW;
  result.x = CW_USEDEFAULT;
  result.y = CW_USEDEFAULT;
  result.width = CW_USEDEFAULT;
  result.height = CW_USEDEFAULT;
  result.parentWindow = NULL;
  result.menu = NULL;
  result.instanceHandle = *instanceHandle;
  result.arbitraryData = NULL;

  return result;
}

HWND createWindow(HINSTANCE* instanceHandle)
{
  registerWindowClass(instanceHandle);
  auto values = mainWindowValues(instanceHandle);

  return CreateWindowExW(
    values.behaviours,
    values.className.c_str(),
    values.titleBar.c_str(),
    values.style,
    values.x, values.y, values.width, values.height,
    values.parentWindow,
    values.menu,
    *instanceHandle,
    values.arbitraryData
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
