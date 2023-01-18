#include <assert.h>
#include <D2d1.h>
#include <windows.h>


template <class DERIVED_TYPE>
class BaseWindow
{
public:
  static LRESULT CALLBACK windowCallback(
    HWND windowHandle, UINT eventType, WPARAM wParam, LPARAM lParam)
  {
    DERIVED_TYPE* pThis = NULL;

    if (eventType == WM_NCCREATE) {
      CREATESTRUCT *pCreate = (CREATESTRUCT*) lParam;
      pThis = (DERIVED_TYPE*) pCreate->lpCreateParams;
      SetWindowLongPtr(windowHandle, GWLP_USERDATA, (LONG_PTR) pThis);

      pThis->windowHandle = windowHandle;
    }

    else
      pThis = (DERIVED_TYPE*) GetWindowLongPtr(windowHandle, GWLP_USERDATA);

    if (pThis)
      return pThis->handleMessage(eventType, wParam, lParam);

    else
      return DefWindowProcW(windowHandle, eventType, wParam, lParam);
  }

  BaseWindow()
  {
    this->windowHandle = NULL;
  }

  BOOL create(
    PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0,
    int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
    int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT,
    HWND hWndParent = 0, HMENU hMenu = 0)
  {
    WNDCLASSW windowClass {0};

    windowClass.lpfnWndProc = DERIVED_TYPE::windowCallback;
    windowClass.hInstance = GetModuleHandle(NULL);
    windowClass.lpszClassName = this->className();

    RegisterClassW(&windowClass);

    this->windowHandle = CreateWindowExW(
      dwExStyle, this->className(), lpWindowName, dwStyle, x, y,
      nWidth, nHeight, hWndParent, hMenu, GetModuleHandleW(NULL), this
    );

    return (this->windowHandle ? TRUE : FALSE);
  }

  HWND window() const
  {
    return this->windowHandle;
  }

protected:
  virtual PCWSTR className() const = 0;
  virtual LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

  HWND windowHandle;
};