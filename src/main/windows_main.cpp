#include <windows.h>

// Declared ahead of time.
LRESULT CALLBACK WindowProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/**
 * @brief Main entry point for the Windows API to launch from.
 * Hence, no refactoring out of legacy parameters due to the interface
 * being set in stone by the API.
 */
int CALLBACK WinMain(
    HINSTANCE instanceHandle, HINSTANCE prevInstance,
    LPSTR commandLineArgs, int minimisedOption)
{
  // Register window class.
  // const wchar_t windowClassName[] = L"Fortesque";

  WNDCLASSA windowClass {};
  windowClass.lpfnWndProc = WindowProc;
  windowClass.hInstance = instanceHandle;
  windowClass.lpszClassName = (LPCSTR) L"Fortesque";

  RegisterClassA(&windowClass);

  // Create window.
  HWND hwnd = CreateWindowExA(
    0,                           // Optional window styles.
    (LPCSTR) L"Fortesque",             // Window class
    (LPCSTR) L"Learn to Program Windows", // Window text
    WS_OVERLAPPEDWINDOW,         // Window style

    // Size and position
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

    NULL,           // Parent window
    NULL,           // Menu
    instanceHandle, // Instance handle
    NULL            // Additional application data
  );

  if (hwnd == NULL)
  {
    return 0;
  }

  ShowWindow(hwnd, minimisedOption);

  // Run the message loop.
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0) > 0)
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;

  return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_PAINT:
  {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // All painting occurs here, between BeginPaint and EndPaint.
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
    EndPaint(hwnd, &ps);
  }
    return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}