#include <windows.h>
#include "main_window.h"


LPCWSTR MainWindow::className() const
{
  return L"Sample Window Class";
}

LRESULT MainWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      
      return 0;

    case WM_PAINT:
    {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(windowHandle, &ps);
      FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
      EndPaint(windowHandle, &ps);
    } return 0;

    default:
      return DefWindowProcW(windowHandle, uMsg, wParam, lParam);
  }

  return TRUE;
}