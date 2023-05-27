#pragma once

enum EventType {
   EVENT_NULL,
   EVENT_PLAYERDED,
   EVENT_PLAYERDAMAGED,
   EVENT_QUIT_GAME,
   EVENT_RESTART_GAME
};

class Listener {
public:
   virtual void processEvent(EventType type) = 0;
};
