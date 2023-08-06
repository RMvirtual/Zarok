#include <windows.h>


HINSTANCE hInst;
HWND hWnd;
HBITMAP hBitmap;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        int width = 200;
        int height = 200;

        // Draw bitmap onto window.
        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hOldBitmap = (HBITMAP) SelectObject(hdcMem, hBitmap);
        BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
        SelectObject(hdcMem, hOldBitmap);
        DeleteDC(hdcMem);

        EndPaint(hWnd, &ps);
        break;
    }

    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    
    return 0;
}


int WINAPI WinMain(
    HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
    int nCmdShow
) {
    hInst = hInstance;
    int width = 400;  
    int height = 300;

    // Create in-memory device context and compatible bitmap.
    HDC hdc = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdc);
    
    hBitmap = CreateCompatibleBitmap(hdc, width, height);
    SelectObject(hdcMem, hBitmap);

    // Draw on in-memory bitmap.
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
    RECT rect {0, 0, width, height};
    FillRect(hdcMem, &rect, hBrush);
    DeleteObject(hBrush);

    // Release resources.
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdc);    

    // Register window class.
    WNDCLASSEXW wcex {
        sizeof(WNDCLASSEXW), CS_HREDRAW | CS_VREDRAW, WndProc, 0L, 0L,
        GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"BitmapWindowClass",
        NULL
    };
    
    RegisterClassExW(&wcex);

    // Create window.
    hWnd = CreateWindowW(
        L"BitmapWindowClass", L"Bitmap Window",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        width, height, NULL, NULL, hInstance, NULL
    );

    // Display window.
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Event loop.
    MSG msg;

    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return (int) msg.wParam;
}
