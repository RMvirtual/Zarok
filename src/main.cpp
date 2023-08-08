#include <windows.h>


HINSTANCE WINDOWS_INSTANCE;
HWND WINDOW_HANDLER;
HBITMAP BITMAP_BUFFER;
INT BITMAP_WIDTH = 400;
INT BITMAP_HEIGHT = 400;

LRESULT CALLBACK processEvent(
    HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(
    HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
    int nCmdShow
) {
    WINDOWS_INSTANCE = hInstance;
    int width = 300;
    int height = 400;

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
        sizeof(WNDCLASSEXW), CS_HREDRAW | CS_VREDRAW, processEvent, 0L, 0L,
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


LRESULT CALLBACK processEvent(
    HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_SIZE: {
        BITMAP_WIDTH = LOWORD(lParam);
        BITMAP_HEIGHT = HIWORD(lParam);

        InvalidateRect(windowHandle, NULL, TRUE); // Trigger a repaint
        break;
    }
    case WM_PAINT: {
        PAINTSTRUCT paintStruct;
        HDC deviceContext = BeginPaint(windowHandle, &paintStruct);

        int width = 300;
        int height = 400;

        // Draw bitmap onto window.
        HDC inMemoryDeviceContext = CreateCompatibleDC(deviceContext);
        
        HBITMAP oldBitmap = (HBITMAP) SelectObject(
            inMemoryDeviceContext, BITMAP_BUFFER);

        StretchBlt(
            deviceContext, 0, 0, BITMAP_WIDTH, BITMAP_HEIGHT,
            inMemoryDeviceContext, 0, 0, width, height, SRCCOPY
        );
        
        /*
        BitBlt(
            deviceContext, 0, 0, width, height, inMemoryDeviceContext,
            0, 0, SRCCOPY
        );
        */
       
        SelectObject(inMemoryDeviceContext, oldBitmap);
        
        DeleteDC(inMemoryDeviceContext);
        EndPaint(windowHandle, &paintStruct);
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
