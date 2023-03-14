#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

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
	Scene* scene;

	std::unordered_map<SDL_Keycode, PlayerCommand> keyMappings;

	void processKeyPress(SDL_Keycode keycode, Uint16 modification);
	bool testControlDown();

public:
	InputManager(GameWindow* window, Scene* scene);

	//Returns false if game needs to be closed
	bool processInput();

	InputConfirmer* presentConfirmer();

	void setScene(Scene* scene);
};



#endif
