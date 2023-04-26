#pragma once

#include <SDL.h>
#include "PlayerManager/PlayerManager.h"

class PlayerUI {
private:
	PlayerManager* playerMan;

	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

public:
	PlayerUI(PlayerManager* playerMan) : playerMan(playerMan), renderer(NULL), spritesheet(NULL) {};

	void initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet);

	void render(const SDL_Rect& viewport);
};
