#pragma once
#include <assert.h>
#include <D2d1.h>
#include <windows.h>


class GraphicsScene
{
protected:
  // D2D Resources
  CComPtr<ID2D1Factory> direct2DFactory;
  CComPtr<ID2D1HwndRenderTarget> renderTarget;

  float scaleX;
  float scaleY;

protected:
  // Derived class must implement these methods.
  virtual HRESULT CreateDeviceIndependentResources() = 0;
  virtual void DiscardDeviceIndependentResources() = 0;
  virtual HRESULT CreateDeviceDependentResources() = 0;
  virtual void DiscardDeviceDependentResources() = 0;
  virtual void CalculateLayout() = 0;
  virtual void RenderScene() = 0;

protected:
  HRESULT CreateGraphicsResources(HWND hwnd)
  {
    HRESULT hr = S_OK;

    if (this->renderTarget == NULL) {
      RECT rc;
      GetClientRect(hwnd, &rc);

      D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

      hr = direct2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hwnd, size),
        &this->renderTarget
      );

      if (SUCCEEDED(hr))
        hr = CreateDeviceDependentResources();

      if (SUCCEEDED(hr))
        CalculateLayout();

    }

    return hr;
  }

  template <class T>
  T PixelToDipX(T pixels) const
  {
    return static_cast<T>(pixels / scaleX);
  }

  template <class T>
  T PixelToDipY(T pixels) const
  {
    return static_cast<T>(pixels / scaleY);
  }

public:
  GraphicsScene()
  {
    this->scaleX = 1.0f;
    this->scaleY = 1.0f;
  }

  virtual ~GraphicsScene()
  {

  }

  HRESULT Initialize()
  {
    HRESULT hr = D2D1CreateFactory(
      D2D1_FACTORY_TYPE_SINGLE_THREADED, &direct2DFactory);

    if (SUCCEEDED(hr))
      CreateDeviceIndependentResources();

    return hr;
  }

  void Render(HWND hwnd)
  {
    HRESULT hr = CreateGraphicsResources(hwnd);

    if (FAILED(hr))
      return;

    assert(renderTarget != NULL);
    renderTarget->BeginDraw();

    RenderScene();

    hr = renderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET) {
      DiscardDeviceDependentResources();
      renderTarget.Release();
    }
  }

  HRESULT Resize(int x, int y)
  {
    HRESULT result = S_OK;

    if (this->renderTarget) {
      result = this->renderTarget->Resize(D2D1::SizeU(x, y));
      
      if (SUCCEEDED(result))
        CalculateLayout();
    }

    return result;
  }

  void CleanUp()
  {
    DiscardDeviceDependentResources();
    DiscardDeviceIndependentResources();
  }
};