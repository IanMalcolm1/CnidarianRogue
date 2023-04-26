#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Adventure/Adventure.h"
#include "GameWindow.h"
#include "Enums/PlayerCommands.h"
#include "UIScreens/InputConfirmer.h"
#include "Scene/Scene.h"
#include <unordered_map>
#include <SDL_events.h>

class InputManager {
private:
	InputConfirmer confirmer;

	GameWindow* gameWindow;
	Adventure* adventure;

	std::unordered_map<SDL_Keycode, PlayerCommand> keyMappings;

	void processKeyPress(SDL_Keycode keycode, Uint16 modification);
	bool testControlDown();

public:
	InputManager(GameWindow* window, Adventure* adventure);

	//Returns false if game needs to be closed
	bool processInput();

	InputConfirmer* getInputConfirmer();
};



#endif
