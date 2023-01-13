#include <windows.h>
#include "windows/demo/direct2D/circle.cpp"

int CALLBACK WinMain(
  HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow)
{
    MainWindow win;

    if (!win.Create(L"Circle", WS_OVERLAPPEDWINDOW))
        return 0;

    ShowWindow(win.Window(), nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}
