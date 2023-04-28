#include "EventListener/Blabber.h"


void Blabber::addListener(Listener* listener) {
   listeners.push_back(listener);
}

void Blabber::notifyListeners(EventType type) {
   for (auto listener : listeners) {
      listener->processEvent(type);
   }
}
