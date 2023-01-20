#pragma once
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "windows/demo/gui/oop/base_window.h"


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
  ID2D1Factory* direct2DFactory;
  ID2D1HwndRenderTarget* renderTarget;
  ID2D1SolidColorBrush* brush;
  D2D1_ELLIPSE ellipse;

  D2D1_SIZE_U handleSize();
  RECT rectangle();
  D2D1_ELLIPSE generateEllipse();
  D2D1_POINT_2F centreCoordinates();
  HRESULT initialiseRenderTarget();
  HRESULT initialiseBrush();
};
