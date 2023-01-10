#pragma once
#include "base_window.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
  LPCWSTR ClassName() const;
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};