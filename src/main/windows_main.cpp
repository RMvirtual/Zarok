#include <windows.h>
#include "src/main/windows/gui.cpp"


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
