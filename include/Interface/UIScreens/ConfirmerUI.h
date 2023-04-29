#pragma once

#include "GraphicsThings/TextRenderer.h"
#include "Interface/InputConfirmer.h"
#include <SDL.h>

class ConfirmerUI {
private:
	InputConfirmer* signaller;

	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

	GameTextMaker textMaker;
	TextRenderer textRenderer;
	TextRenderingSpecs textSpecs;

	GameText yes, no;
	SDL_Rect parentViewport;
	SDL_Rect screenViewport, yesViewport, noViewport;

	bool highlightYes, highlightNo;

	void calcDimensions(const SDL_Rect& viewport);

public:
	bool hidden;

	ConfirmerUI(int fontSize = 4) : signaller(NULL), renderer(NULL), spritesheet(NULL),
   parentViewport({ 0,0,0,0 }), yesViewport({ 0,0,0,0 }), noViewport({ 0,0,0,0 }),
   screenViewport({ 0,0,0,0 }), highlightYes(false), highlightNo(false),
   textRenderer(), textSpecs(fontSize), yes(), no(), textMaker(), hidden(true) {};

	void initialize(InputConfirmer* signaller, SDL_Renderer* renderer, SDL_Texture* spritesheet);

	void render(const SDL_Rect& viewport);

	void processMouseLocation(int x, int y);
	void processMouseClick(int x, int y);
	void processKeyPress(SDL_Keycode keycode);
};
