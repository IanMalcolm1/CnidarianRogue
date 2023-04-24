#pragma once

#include <SDL.h>
#include "PlayerManager/PlayerManager.h"

class PlayerUI {
private:
	ActorEntity* player;

	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

public:
	PlayerUI() : player(NULL), renderer(NULL), spritesheet(NULL) {};

	void initialize(PlayerManager* playerManager, SDL_Renderer* renderer, SDL_Texture* spritesheet);

	void render(const SDL_Rect& viewport);

	void processCursorLocation(int x, int y);
	void processScroll(int x, int y, int offset, bool ctrlDown);
	void processClick(int x, int y, bool ctrlDown);
};
