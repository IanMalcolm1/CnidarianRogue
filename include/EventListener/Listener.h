#pragma once

enum EventType {
   EVENT_NULL,
   EVENT_PLAYERDED
};

class Listener {
public:
   virtual void processEvent(EventType type) = 0;
};
