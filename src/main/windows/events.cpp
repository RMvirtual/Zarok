#pragma once
#include <windows.h>

struct EventHandler
{
  MSG event;

  EventHandler()
  {
    this->event = {};
  }

  bool eventAvailable()
  {
    return GetMessageW(&this->event, NULL, 0, 0) > 0;
  }

  void processEvent()
  {
    TranslateMessage(&this->event);
    DispatchMessageW(&this->event);
  }

  void run()
  {
    while (this->eventAvailable())
      this->processEvent();
  }
};

