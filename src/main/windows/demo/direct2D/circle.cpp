#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "circle.h"
#include "windows/demo/gui/oop/base_window.h"

MainWindow::MainWindow() : direct2DFactory(NULL), renderTarget(NULL), brush(NULL)
{
  // Pass.
}

PCWSTR MainWindow::className() const
{
  return L"Zarok";
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
  if (this->renderTarget != NULL)
    this->ellipse = this->generateEllipse();
}

D2D1_ELLIPSE MainWindow::generateEllipse()
{
  const auto coordinates = this->centreCoordinates();
  const float radius = min(coordinates.x, coordinates.y);
  
  return D2D1::Ellipse(coordinates, radius, radius);
}

D2D1_POINT_2F MainWindow::centreCoordinates()
{
  auto size = this->renderTarget->GetSize();

  return D2D1::Point2F(size.width / 2, size.height / 2);
}

HRESULT MainWindow::createGraphicsResources()
{
  HRESULT result = S_OK;

  if (this->renderTarget == NULL) {
    result = this->initialiseRenderTarget();

    if (SUCCEEDED(result)) {
      result = this->initialiseBrush();

      if (SUCCEEDED(result))
        this->calculateLayout();
    }
  }

  return result;
}

HRESULT MainWindow::initialiseBrush()
{
  const auto color = D2D1::ColorF(1.0f, 1.0f, 0);
  
  return this->renderTarget->CreateSolidColorBrush(color, &this->brush);
}

HRESULT MainWindow::initialiseRenderTarget()
{
  auto rectangle = this->rectangle();
  auto size = D2D1::SizeU(rectangle.right, rectangle.bottom);

  return this->direct2DFactory->CreateHwndRenderTarget(
    D2D1::RenderTargetProperties(),
    D2D1::HwndRenderTargetProperties(this->windowHandle, size),
    &this->renderTarget
  );
}

void MainWindow::discardGraphicsResources()
{
  SafeRelease(&this->renderTarget);
  SafeRelease(&this->brush);
}

void MainWindow::onPaint()
{
  HRESULT result = this->createGraphicsResources();

  if (SUCCEEDED(result)) {
    PAINTSTRUCT ps;
    BeginPaint(this->windowHandle, &ps);

    this->renderTarget->BeginDraw();
    this->renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
    this->renderTarget->FillEllipse(ellipse, brush);

    result = renderTarget->EndDraw();

    if (FAILED(result) || result == D2DERR_RECREATE_TARGET)
      this->discardGraphicsResources();

    EndPaint(this->windowHandle, &ps);
  }
}

void MainWindow::resize()
{
  if (this->renderTarget == NULL)
    return;

  this->renderTarget->Resize(this->handleSize());
  this->calculateLayout();
  InvalidateRect(this->windowHandle, NULL, FALSE);
}

D2D1_SIZE_U MainWindow::handleSize()
{
  auto rectangle = this->rectangle();
  
  return D2D1::SizeU(rectangle.right, rectangle.bottom);
}

RECT MainWindow::rectangle()
{
  RECT result;
  GetClientRect(windowHandle, &result);

  return result;
}

LRESULT MainWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg) {
    case WM_CREATE:
      if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &direct2DFactory)))
        return -1;

      return 0;

    case WM_DESTROY:
      this->discardGraphicsResources();
      SafeRelease(&direct2DFactory);
      PostQuitMessage(0);

      return 0;

    case WM_PAINT:
      onPaint();

      return 0;

    case WM_SIZE:
      resize();

      return 0;
  }

  return DefWindowProcW(windowHandle, uMsg, wParam, lParam);
}