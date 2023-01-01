#pragma once
#include <windows.h>
#include "windows/gui/main_menu.h"

/**
 * @brief Main entry point for the Windows API to launch from.
 */
int CALLBACK WinMain(
    HINSTANCE instanceHandle, HINSTANCE prevInstance,
    LPSTR commandLineArgs, int minimisationOption)
{
  launchMainWindow(createWindow(&instanceHandle), minimisationOption);

  return 0;
}
