#include <iostream>
#include <Windows.h>

LRESULT CALLBACK mainWindowCallback(
  HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT result = 0;

  switch(message) {
    case WM_SIZE: {
      OutputDebugStringA("WM_SIZE\n");
      std::cout << "Size\n";
    } break;
    
    case WM_DESTROY: {
      OutputDebugStringA("WM_DESTROY\n");
    } break;
    
    case WM_CLOSE: {
      OutputDebugStringA("WM_CLOSE\n");
    } break;
    
    case WM_ACTIVATEAPP: {
      OutputDebugStringA("WM_ACTIVATEAPP\n");
    } break;
    
    default: {
      result = DefWindowProc(window, message, wParam, lParam);
    } break;
  }

  return result;
}

int CALLBACK WinMain(
  HINSTANCE instance, HINSTANCE prevInstance, LPSTR commandLine, int showCode)
{
  WNDCLASS windowClass {};

  windowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
  windowClass.lpfnWndProc = mainWindowCallback;
  windowClass.hInstance = instance;
  windowClass.lpszClassName = "CompilerTestWindowClass";

  if (RegisterClass(&windowClass)) {
    HWND windowHandle = CreateWindowEx(
      0, windowClass.lpszClassName, "Compiler Test", 
      WS_OVERLAPPEDWINDOW|WS_VISIBLE,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
      0, 0, instance, 0
    );

    if (windowHandle) {
      while (true) {
        MSG message;
        BOOL messageResult = GetMessage(&message, 0, 0, 0);

        if (messageResult > 0) {
          TranslateMessage(&message);
          DispatchMessageA(&message);
        }

        else
          break;
      }
    }
  }

  return 0;
}
