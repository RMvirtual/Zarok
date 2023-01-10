#include <string>
#include <windows.h>
#include "main_menu.h"
#include "events.h"

LRESULT CALLBACK updateCallback(
  HWND windowHandle, UINT eventType, WPARAM wParam, LPARAM lParam)
{
  switch (eventType) {
    case WM_CLOSE: {
      auto quitPrompt = MessageBoxW(
        windowHandle, L"Would you like to quit?", L"HMMM...", MB_OKCANCEL);

      bool shouldQuit = quitPrompt == IDOK;

      if (shouldQuit)
        DestroyWindow(windowHandle);
    } return 0;

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

  return DefWindowProcW(windowHandle, eventType, wParam, lParam);
}

WNDCLASSW windowClass(HINSTANCE* instanceHandle)
{
  WNDCLASSW windowClass {};
  windowClass.lpfnWndProc = updateCallback;
  windowClass.hInstance = *instanceHandle;
  windowClass.lpszClassName = L"Zarok";

  return windowClass;
}

void registerWindowClass(HINSTANCE* instanceHandle)
{
  RegisterClassW(&windowClass(instanceHandle));
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
    values.instanceHandle,
    values.arbitraryData
  );
}

void launchMainWindow(HWND windowHandle, int minimisationOption)
{
  ShowWindow(windowHandle, minimisationOption);
  EventHandler eventHandler {};
  eventHandler.run();
}