#include <windows.h>
#include "windows/demo/gui/oop/main_window.h"


int CALLBACK WinMain(
  HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow)
{
    MainWindow win;

    if (!win.create(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW))
      return 0;

    ShowWindow(win.window(), nCmdShow);

    MSG msg = {};

    while (GetMessageW(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessageW(&msg);
    }

    return 0;
}