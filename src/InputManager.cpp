#include "Interface/InputManager.h"
#include <stdexcept>


InputManager::InputManager(GameWindow* window, Adventure* adventure) :
	gameWindow(window), adventure(adventure), confirmer(InputConfirmer()) {

	keyMappings = std::unordered_map<SDL_Keycode, PlayerCommand>();

	//TODO: move these defaults to a settings file
	keyMappings.insert({ SDLK_UP, PC_NORTH });
	keyMappings.insert({ SDLK_DOWN, PC_SOUTH });
	keyMappings.insert({ SDLK_RIGHT, PC_EAST });
	keyMappings.insert({ SDLK_LEFT, PC_WEST });
	keyMappings.insert({ SDLK_u, PC_NORTH_EAST });
	keyMappings.insert({ SDLK_y, PC_NORTH_WEST });
	keyMappings.insert({ SDLK_j, PC_SOUTH_EAST });
	keyMappings.insert({ SDLK_h, PC_SOUTH_WEST });

	keyMappings.insert({ SDLK_PERIOD, PC_WAIT });

	keyMappings.insert({ SDLK_l, PC_TOGGLE_LOOK });

	keyMappings.insert({ SDLK_ESCAPE, PC_ESCAPEKEY });

	/* Unimplemented
	keyMappings.insert({ SDLK_i, PI_INV });
	keyMappings.insert({ SDLK_PERIOD, PI_WAIT });
	keyMappings.insert({ SDLK_COMMA, PI_PICKUP });
	*/

}


InputConfirmer* InputManager::getInputConfirmer() {
	return &confirmer;
}

bool InputManager::processInput() {
	if (confirmer.isAwaiting()) {
		if (confirmer.getConfirmation() == CONF_CONFIRMED) {
			if (confirmer.commandEquals(PC_QUITGAME)) {
				return false;
			}
		}
	}

	SDL_Event sdlEvent;
	bool controlDown = testControlDown();

	int x, y;
	SDL_GetMouseState(&x, &y);

	gameWindow->processCursorLocation(x, y);
	

	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_KEYDOWN:
			processKeyPress(sdlEvent.key.keysym.sym, sdlEvent.key.keysym.mod);
			break;

		case SDL_MOUSEWHEEL:
			//zooming in/out
			gameWindow->processScroll(x, y, sdlEvent.wheel.y, controlDown);
			break;

		case SDL_WINDOWEVENT:
			if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED) {
				gameWindow->updateWindowDimensions(sdlEvent.window.data1, sdlEvent.window.data2);
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			gameWindow->processClick(x, y, controlDown);
			break;

		case SDL_QUIT: //user closes window using the red x
			confirmer.signalPopup(PC_QUITGAME, "Quit Game?");
			break;
		}
	}

	return true;
}

void InputManager::processKeyPress(SDL_Keycode keycode, Uint16 modification) {
	gameWindow->processKeyPress(keycode);

	if (confirmer.isAwaiting()) {
		return;
	}

	PlayerCommand command;
	if (keyMappings.find(keycode) == keyMappings.end()) {
		return;
	}

	command = keyMappings.at(keycode);

	if (command < PC_END_OF_PLAYER_ACTIONS) {
      adventure->processCommand(command, modification);
   }
}

bool InputManager::testControlDown() {
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

	if (keyStates[SDL_SCANCODE_LCTRL] || keyStates[SDL_SCANCODE_RCTRL]) {
		return true;
	}
	return false;
}
