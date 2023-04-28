#pragma once

#include "EventListener/Listener.h"
#include <vector>


class Blabber {
private:
   std::vector<Listener*> listeners;

public:
   void addListener(Listener* listener);
   void notifyListeners(EventType type);
};
