#include "Interface/UIScreens/GameOverUI.h"

void GameOverUI::processKeyPress(SDL_Keycode keycode) {
	if (hidden) {
		return;
	}

	if (keycode == SDLK_r) {
      onLeftButtonSelect();
      hidden = true;
	}
	else if (keycode == SDLK_q) {
      onRightButtonSelect();
      hidden = true;
	}
}

void GameOverUI::onLeftButtonSelect() {
   notifyListeners(EVENT_RESTART_GAME);
}
void GameOverUI::onRightButtonSelect() {
   notifyListeners(EVENT_QUIT_GAME);
}
