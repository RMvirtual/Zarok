#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "circle.h"
#include "windows/demo/gui/oop/base_window.h"

MainWindow::MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL)
{
  // Pass.
}

PCWSTR MainWindow::className() const
{
  return L"Circle Window Class";
}

template <class T>
void SafeRelease(T **ppT)
{
  if (*ppT) {
    (*ppT)->Release();
    *ppT = NULL;
  }
}

void MainWindow::calculateLayout()
{
  if (pRenderTarget != NULL) {
    D2D1_SIZE_F size = pRenderTarget->GetSize();
    const float x = size.width / 2;
    const float y = size.height / 2;
    const float radius = min(x, y);
    ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
  }
}

HRESULT MainWindow::createGraphicsResources()
{
  HRESULT hr = S_OK;

  if (pRenderTarget == NULL) {
    RECT rc;
    GetClientRect(m_hwnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

    hr = pFactory->CreateHwndRenderTarget(
      D2D1::RenderTargetProperties(),
      D2D1::HwndRenderTargetProperties(m_hwnd, size),
      &pRenderTarget
    );

    if (SUCCEEDED(hr)) {
      const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);
      hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);

      if (SUCCEEDED(hr))
        calculateLayout();
    }
  }

  return hr;
}

void MainWindow::discardGraphicsResources()
{
  SafeRelease(&pRenderTarget);
  SafeRelease(&pBrush);
}

void MainWindow::onPaint()
{
  HRESULT hr = createGraphicsResources();

  if (SUCCEEDED(hr)) {
    PAINTSTRUCT ps;
    BeginPaint(m_hwnd, &ps);

    pRenderTarget->BeginDraw();

    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
    pRenderTarget->FillEllipse(ellipse, pBrush);

    hr = pRenderTarget->EndDraw();

    if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
      discardGraphicsResources();

    EndPaint(m_hwnd, &ps);
  }
}

void MainWindow::resize()
{
  if (pRenderTarget == NULL)
    return;

  auto rectangle = this->rectangle();
  D2D1_SIZE_U size = D2D1::SizeU(rectangle.right, rectangle.bottom);

  pRenderTarget->Resize(size);
  this->calculateLayout();
  InvalidateRect(m_hwnd, NULL, FALSE);
}

RECT MainWindow::rectangle()
{
  RECT result;
  GetClientRect(m_hwnd, &result);

  return result;
}

LRESULT MainWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg) {
    case WM_CREATE:
      if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
        return -1;

      return 0;

    case WM_DESTROY:
      discardGraphicsResources();
      SafeRelease(&pFactory);
      PostQuitMessage(0);

      return 0;

    case WM_PAINT:
      onPaint();

      return 0;

    case WM_SIZE:
      resize();

      return 0;
  }

  return DefWindowProcW(m_hwnd, uMsg, wParam, lParam);
}