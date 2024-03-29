#include <windows.h>
#include "draw.h"

HINSTANCE WINDOWS_INSTANCE;
HWND WINDOW;
HBITMAP BITMAP_BUFFER;
INT BITMAP_WIDTH = 400;
INT BITMAP_HEIGHT = 400;
bool IS_DRAWING = FALSE;
POINT LAST_POINT;


LRESULT CALLBACK processEvent(
    HWND window, UINT event, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(
    HINSTANCE windowsInstance, HINSTANCE previousWindowsInstance,
    LPSTR lpCmdLine, int nCmdShow
) {
    WINDOWS_INSTANCE = windowsInstance;
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
    WINDOW = CreateWindowW(
        L"BitmapWindowClass", L"Zarok",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        width, height, NULL, NULL, windowsInstance, NULL
    );

    // Display window.
    ShowWindow(WINDOW, nCmdShow);
    UpdateWindow(WINDOW);

    // Event loop.
    MSG event;

    while (GetMessageW(&event, NULL, 0, 0)) {
        TranslateMessage(&event);
        DispatchMessageW(&event);
    }

    return (int) event.wParam;
}


LRESULT CALLBACK processEvent(
    HWND window, UINT event, WPARAM wParam, LPARAM lParam)
{
    switch (event) {
    case WM_SIZE: {
        BITMAP_WIDTH = LOWORD(lParam);
        BITMAP_HEIGHT = HIWORD(lParam);

        InvalidateRect(window, NULL, TRUE);  // Trigger repaint.
        break;
    }

    case WM_LBUTTONDOWN:
        IS_DRAWING = true;
        LAST_POINT.x = LOWORD(lParam);
        LAST_POINT.y = HIWORD(lParam);
        break;

    case WM_LBUTTONUP:
        IS_DRAWING = false;
        break;

    case WM_MOUSEMOVE:
        if (IS_DRAWING) {
            HDC deviceContext = GetDC(window);
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);

            drawLineSegment(deviceContext, LAST_POINT.x, LAST_POINT.y, x, y);
            ReleaseDC(window, deviceContext);
            
            LAST_POINT.x = x;
            LAST_POINT.y = y;
        }

    case WM_PAINT: {
        PAINTSTRUCT paintStruct;
        HDC deviceContext = BeginPaint(window, &paintStruct);

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
               
        SelectObject(inMemoryDeviceContext, oldBitmap);
        
        DeleteDC(inMemoryDeviceContext);
        EndPaint(window, &paintStruct);
        break;
    }

    case WM_CLOSE:
        DestroyWindow(window);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(window, event, wParam, lParam);
    }
    
    return 0;
}
