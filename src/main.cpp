#include <windows.h>


HINSTANCE WINDOWS_INSTANCE;
HWND WINDOW_HANDLER;
HBITMAP BITMAP_BUFFER;


LRESULT CALLBACK WndProc(
    HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(windowHandle, &ps);

        int width = 200;
        int height = 200;

        // Draw bitmap onto window.
        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hOldBitmap = (HBITMAP) SelectObject(hdcMem, BITMAP_BUFFER);
        BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
        SelectObject(hdcMem, hOldBitmap);
        DeleteDC(hdcMem);

        EndPaint(windowHandle, &ps);
        break;
    }

    case WM_CLOSE:
        DestroyWindow(windowHandle);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(windowHandle, message, wParam, lParam);
    }
    
    return 0;
}


int WINAPI WinMain(
    HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
    int nCmdShow
) {
    WINDOWS_INSTANCE = hInstance;
    int width = 400;  
    int height = 300;

    // Create in-memory device context and compatible bitmap.
    HDC deviceContext = GetDC(NULL);
    HDC deviceContextBuffer = CreateCompatibleDC(deviceContext);
    
    BITMAP_BUFFER = CreateCompatibleBitmap(deviceContext, width, height);
    SelectObject(deviceContextBuffer, BITMAP_BUFFER);

    // Draw on in-memory bitmap.
    HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
    RECT rectangle {0, 0, width, height};
    FillRect(deviceContextBuffer, &rectangle, brush);
    DeleteObject(brush);

    // Release resources.
    DeleteDC(deviceContextBuffer);
    ReleaseDC(NULL, deviceContext);    

    // Register window class.
    WNDCLASSEXW windowClass {
        sizeof(WNDCLASSEXW), CS_HREDRAW | CS_VREDRAW, WndProc, 0L, 0L,
        GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"BitmapWindowClass",
        NULL
    };
    
    RegisterClassExW(&windowClass);

    // Create window.
    WINDOW_HANDLER = CreateWindowW(
        L"BitmapWindowClass", L"Bitmap Window",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        width, height, NULL, NULL, hInstance, NULL
    );

    // Display window.
    ShowWindow(WINDOW_HANDLER, nCmdShow);
    UpdateWindow(WINDOW_HANDLER);

    // Event loop.
    MSG event;

    while (GetMessageW(&event, NULL, 0, 0)) {
        TranslateMessage(&event);
        DispatchMessageW(&event);
    }

    return (int) event.wParam;
}
