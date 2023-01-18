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
  HRESULT CreateGraphicsResources(HWND windowHandle)
  {
    HRESULT result = S_OK;

    if (this->renderTarget == NULL) {
      RECT rectangle;
      GetClientRect(windowHandle, &rectangle);

      D2D1_SIZE_U size = D2D1::SizeU(rectangle.right, rectangle.bottom);

      result = direct2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(windowHandle, size),
        &this->renderTarget
      );

      if (SUCCEEDED(result))
        result = CreateDeviceDependentResources();

      if (SUCCEEDED(result))
        CalculateLayout();
    }

    return result;
  }

  template <class T>
  T PixelToDipX(T pixels) const
  {
    return static_cast<T>(pixels / this->scaleX);
  }

  template <class T>
  T PixelToDipY(T pixels) const
  {
    return static_cast<T>(pixels / this->scaleY);
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

  HRESULT initialise()
  {
    HRESULT result = D2D1CreateFactory(
      D2D1_FACTORY_TYPE_SINGLE_THREADED, &direct2DFactory);

    if (SUCCEEDED(result))
      CreateDeviceIndependentResources();

    return result;
  }

  void render(HWND windowHandle)
  {
    HRESULT result = CreateGraphicsResources(windowHandle);

    if (FAILED(result))
      return;

    assert(this->renderTarget != NULL);
    renderTarget->BeginDraw();

    RenderScene();

    result = renderTarget->EndDraw();

    if (result == D2DERR_RECREATE_TARGET) {
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