#pragma once
#include "windows/demo/gui/oop/base_window.h"
#include <d2d1.h>
#pragma comment(lib, "d2d1")


class MainWindow : public BaseWindow<MainWindow>
{
public:
  MainWindow();
  void calculateLayout();
  HRESULT createGraphicsResources();
  void discardGraphicsResources();
  void onPaint();
  void resize();
  LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
  PCWSTR className() const;

private:
  ID2D1Factory *pFactory;
  ID2D1HwndRenderTarget *pRenderTarget;
  ID2D1SolidColorBrush *pBrush;
  D2D1_ELLIPSE ellipse;

  D2D1_SIZE_U handleSize();
  RECT rectangle();

};
