#include <windows.h>

LRESULT CALLBACK updateCallback(
  HWND windowHandle, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg) {
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

  return DefWindowProcW(windowHandle, uMsg, wParam, lParam);
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

/**
 * @brief Main entry point for the Windows API to launch from.
 * Hence, no refactoring out of legacy parameters due to the interface
 * being set in stone by the API.
 */
int CALLBACK WinMain(
    HINSTANCE instanceHandle, HINSTANCE prevInstance,
    LPSTR commandLineArgs, int minimisationOption)
{
  const wchar_t windowClassName[] = L"Fortesque";
  registerWindowClass(&instanceHandle);

  // Create window.
  HWND windowHandle = CreateWindowExW(
    0,                           // Optional window styles.
    windowClassName,             // Window class
    L"Fortesque", // Window text
    WS_OVERLAPPEDWINDOW,         // Window style

    // Size and position
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

    NULL,           // Parent window
    NULL,           // Menu
    instanceHandle, // Instance handle
    NULL            // Additional application data
  );

  if (windowHandle == NULL)
    return 0;

  ShowWindow(windowHandle, minimisationOption);

  // Run the message loop.
  MSG message = {};
  while (GetMessage(&message, NULL, 0, 0) > 0) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }

  return 0;
}
