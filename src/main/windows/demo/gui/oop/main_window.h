#pragma once
#include "base_window.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
  LPCWSTR className() const;
  LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};