#pragma once

#include <SDL.h>
#include "Adventure/PlayerManager.h"
#include "GraphicsThings/GameText.h"
#include "GraphicsThings/TextRenderer.h"

class PlayerUI {
private:
	PlayerManager* playerMan;

	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

   GameTextMaker textMaker;
	TextRenderer textRenderer;
	TextRenderingSpecs textSpecs;

public:
	PlayerUI(PlayerManager* playerMan, int fontSize = 3) : playerMan(playerMan), renderer(NULL), spritesheet(NULL), textMaker(), textRenderer(), textSpecs(fontSize) {};

	void initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet);

	void render(const SDL_Rect& viewport);
};
