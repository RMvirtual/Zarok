#pragma once
#include <string>
#include <windows.h>

struct WindowValues
{
  DWORD behaviours;
  std::wstring className;
  std::wstring titleBar;
  DWORD style;
  int x; int y; int width; int height;
  HWND parentWindow;
  HMENU menu;
  HINSTANCE instanceHandle;
  LPVOID arbitraryData;
};

LRESULT CALLBACK updateCallback(
  HWND windowHandle, UINT eventType, WPARAM wParam, LPARAM lParam);

WNDCLASSW windowClass(HINSTANCE* instanceHandle);
void registerWindowClass(HINSTANCE* instanceHandle);
WindowValues mainWindowValues(HINSTANCE* instanceHandle);
HWND createWindow(HINSTANCE* instanceHandle);
void launchMainWindow(HWND windowHandle, int minimisationOption);
