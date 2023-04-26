#include "Interface/UIScreens/PlayerUI.h"
#include "Adventure/PlayerManager.h"

void PlayerUI::initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	this->renderer = renderer;
	this->spritesheet = spritesheet;
}

void PlayerUI::render(const SDL_Rect& viewport) {
}
