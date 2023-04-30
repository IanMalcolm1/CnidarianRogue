#include "Interface/UIScreens/ExitConfirmerUI.h"
#include "EventListener/Listener.h"


void ExitConfirmerUI::processKeyPress(SDL_Keycode keycode) {
	if (hidden) {
		return;
	}

	if (keycode == SDLK_y) {
      notifyListeners(EVENT_QUIT_GAME);
		hidden = true;
	}
	else if (keycode == SDLK_n || keycode == SDLK_ESCAPE) {
		hidden = true;
	}
}

void ExitConfirmerUI::onLeftButtonSelect() {
   notifyListeners(EVENT_QUIT_GAME);
}
void ExitConfirmerUI::onRightButtonSelect() {
   return;
}

