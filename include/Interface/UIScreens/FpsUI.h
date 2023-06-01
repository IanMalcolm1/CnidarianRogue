#pragma once

#include "GraphicsThings/GameText.h"
#include "GraphicsThings/TextRenderer.h"
#include "SDL.h"

class FpsUI {
private:
   SDL_Rect viewport;

	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

   TextRenderingSpecs textSpecs;
   GameTextMaker textMaker;
   TextRenderer textRenderer;

   bool hidden;

   void updateViewport(const SDL_Rect& screenDimensions);
   void toggleHidden();

public:
   FpsUI() : hidden(true), textSpecs(2), textMaker(), textRenderer(), viewport() {};

	void initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet);

   void render(const SDL_Rect& screenDimensions, int fps);

	void processKeyPress(SDL_Keycode keycode, SDL_Keymod modification);
};
