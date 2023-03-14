#include "UIScreens/PlayerUI.h"

void PlayerUI::initialize(PlayerManager* playerManager, SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	playerMan = playerManager;
	this->renderer = renderer;
	this->spritesheet = spritesheet;
}

void PlayerUI::render(const SDL_Rect& viewport) {
	if (hidden) {
		return;
	}
}
