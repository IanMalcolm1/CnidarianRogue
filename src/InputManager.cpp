#include "Interface/InputManager.h"
#include "Enums/PlayerCommands.h"
#include "EventListener/Listener.h"
#include "SDL_mouse.h"
#include <stdexcept>


InputManager::InputManager(GameWindow* window, Adventure* adventure) :
gameWindow(window), adventure(adventure) {

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

	keyMappings.insert({ SDLK_COMMA, PC_PICKUP });
	keyMappings.insert({ SDLK_PERIOD, PC_WAIT });
	keyMappings.insert({ SDLK_f, PC_USE_ABILITY });

	keyMappings.insert({ SDLK_l, PC_TOGGLE_LOOK });
   keyMappings.insert({ SDLK_t, PC_TOGGLE_SELECT });

   keyMappings.insert({ SDLK_RETURN, PC_CONFIRM });
	keyMappings.insert({ SDLK_ESCAPE, PC_ESCAPEKEY });
}


bool InputManager::processInput() {
	SDL_Event sdlEvent;
	bool controlDown = testControlDown();

	int x, y;
	SDL_GetMouseState(&x, &y);
	gameWindow->processCursorLocation(x, y);


	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_KEYDOWN:
			processKeyPress(sdlEvent.key.keysym.sym, (SDL_Keymod) sdlEvent.key.keysym.mod);
			break;

		case SDL_MOUSEWHEEL:
			//zooming in/out
			gameWindow->processScroll(x, y, sdlEvent.wheel.y, controlDown);
			break;

      case SDL_MOUSEMOTION:
         gameWindow->processCursorMovement();
         break;

		case SDL_WINDOWEVENT:
			if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED) {
				gameWindow->updateWindowDimensions(sdlEvent.window.data1, sdlEvent.window.data2);
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
         processClick(sdlEvent.button);
			break;

		case SDL_QUIT: //user closes the window
         gameWindow->showExitConfirmationPopup();
			break;
		}
	}

	return true;
}

void InputManager::processKeyPress(SDL_Keycode keycode, SDL_Keymod modification) {
	gameWindow->processKeyPress(keycode, modification);


	PlayerCommand command;
	if (keyMappings.find(keycode) == keyMappings.end()) {
		return;
	}

	command = keyMappings.at(keycode);

	if ((command < PC_END_OF_PLAYER_ACTIONS || command == PC_ESCAPEKEY)&& !gameWindow->isShowingPopups()) {
      adventure->processCommand(command, modification);
   }
}


void InputManager::processClick(SDL_MouseButtonEvent& click) {
   bool isRightClick = click.button==SDL_BUTTON_RIGHT ? true : false;
	gameWindow->processClick(click.x, click.y, isRightClick);
}


bool InputManager::testControlDown() {
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

	if (keyStates[SDL_SCANCODE_LCTRL] || keyStates[SDL_SCANCODE_RCTRL]) {
		return true;
	}
	return false;
}
