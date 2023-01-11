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
      return pThis->HandleMessage(eventType, wParam, lParam);

    else
      return DefWindowProcW(windowHandle, eventType, wParam, lParam);
  }

  BaseWindow() : m_hwnd(NULL)
  {
    // pass.
  }

  BOOL Create(
    PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0,
    int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
    int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT,
    HWND hWndParent = 0, HMENU hMenu = 0)
  {
    WNDCLASSW wc {};

    wc.lpfnWndProc = DERIVED_TYPE::updateCallback;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.lpszClassName = this->ClassName();

    RegisterClassW(&wc);

    m_hwnd = CreateWindowExW(
      dwExStyle, this->ClassName(), L"Zarok", dwStyle, x, y,
      nWidth, nHeight, hWndParent, hMenu, GetModuleHandleW(NULL), this
    );

    return (m_hwnd ? TRUE : FALSE);
  }

  HWND Window() const
  {
    return m_hwnd;
  }

protected:
  virtual LPCWSTR ClassName() const = 0;
  virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

  HWND m_hwnd;
};