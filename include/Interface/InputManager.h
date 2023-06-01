#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Adventure/Adventure.h"
#include "EventListener/Listener.h"
#include "GameWindow.h"
#include "Enums/PlayerCommands.h"
#include "Interface/InputConfirmer.h"
#include "Adventure/Scene/Scene.h"
#include <unordered_map>
#include <SDL_events.h>

class InputManager {
private:
	GameWindow* gameWindow;
	Adventure* adventure;

	std::unordered_map<SDL_Keycode, PlayerCommand> keyMappings;

	void processKeyPress(SDL_Keycode keycode, SDL_Keymod modification);
   void processClick(SDL_MouseButtonEvent& click);
	bool testControlDown();

public:
	InputManager(GameWindow* window, Adventure* adventure);

	//Returns false if game needs to be closed
	bool processInput();

   void processEvent(EventType event);
};



#endif
