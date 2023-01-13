#pragma once
#include "windows/demo/gui/oop/base_window.h"
#include <d2d1.h>
#pragma comment(lib, "d2d1")


class MainWindow : public BaseWindow<MainWindow>
{
public:
  MainWindow();
  void CalculateLayout();
  HRESULT CreateGraphicsResources();
  void DiscardGraphicsResources();
  void OnPaint();
  void Resize();
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
  PCWSTR ClassName() const;

private:
  ID2D1Factory *pFactory;
  ID2D1HwndRenderTarget *pRenderTarget;
  ID2D1SolidColorBrush *pBrush;
  D2D1_ELLIPSE ellipse;

};
