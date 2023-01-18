#pragma once
#include <string>
#include <windows.h>


template <class DERIVED_TYPE>
class BaseWindow
{
public:
  static LRESULT CALLBACK updateCallback(
      HWND windowHandle, UINT eventType, WPARAM wParam, LPARAM lParam)
  {
    DERIVED_TYPE *pThis = NULL;

    if (eventType == WM_NCCREATE) {
      CREATESTRUCT* pCreate = (CREATESTRUCT*) lParam;
      pThis = (DERIVED_TYPE*) pCreate->lpCreateParams;
      SetWindowLongPtrW(windowHandle, GWLP_USERDATA, (LONG_PTR) pThis);

      pThis->m_hwnd = windowHandle;
    }

    else
      pThis = (DERIVED_TYPE*) GetWindowLongPtrW(windowHandle, GWLP_USERDATA);

    if (pThis)
      return pThis->handleMessage(eventType, wParam, lParam);

    else
      return DefWindowProcW(windowHandle, eventType, wParam, lParam);
  }

  BaseWindow() : windowHandle(NULL)
  {
    // pass.
  }

  BOOL create(
    PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0,
    int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
    int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT,
    HWND hWndParent = 0, HMENU hMenu = 0)
  {
    WNDCLASSW wc {};

    wc.lpfnWndProc = DERIVED_TYPE::updateCallback;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.lpszClassName = this->className();

    RegisterClassW(&wc);

    windowHandle = CreateWindowExW(
      dwExStyle, this->className(), L"Zarok", dwStyle, x, y,
      nWidth, nHeight, hWndParent, hMenu, GetModuleHandleW(NULL), this
    );

    return (windowHandle ? TRUE : FALSE);
  }

  HWND window() const
  {
    return windowHandle;
  }

protected:
  virtual LPCWSTR className() const = 0;
  virtual LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

  HWND windowHandle;
};