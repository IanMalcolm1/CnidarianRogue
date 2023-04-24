#include "UIScreens/PlayerUI.h"
#include "PlayerManager/PlayerManager.h"

void PlayerUI::initialize(PlayerManager* playerMan, SDL_Renderer* renderer, SDL_Texture* spritesheet) {
   player = playerMan->getPlayer();
	this->renderer = renderer;
	this->spritesheet = spritesheet;
}

void PlayerUI::render(const SDL_Rect& viewport) {
}
