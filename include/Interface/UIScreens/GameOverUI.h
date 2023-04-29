#pragma once

#include "EventListener/Blabber.h"
#include "GraphicsThings/GameText.h"
#include "GraphicsThings/TextRenderer.h"
#include <SDL.h>


class GameOverUI : public Blabber {
private:
	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

	GameTextMaker textMaker;
	TextRenderer textRenderer;
	TextRenderingSpecs textSpecs;

	GameText gameOverText, restartText, quitText;
	SDL_Rect parentViewport;
	SDL_Rect screenViewport, restartViewport, quitViewport;

	bool highlightRestart, highlightQuit;

	void calcDimensions(const SDL_Rect& viewport);

public:
   bool hidden;

	GameOverUI(int fontSize = 4) : renderer(NULL), spritesheet(NULL),
   parentViewport({ 0,0,0,0 }), restartViewport({ 0,0,0,0 }),
   quitViewport({ 0,0,0,0 }), screenViewport({ 0,0,0,0 }), highlightRestart(false),
   highlightQuit(false), textRenderer(), textSpecs(fontSize), restartText(),
   quitText(), gameOverText(), textMaker(), hidden(true) {};

	void initialize(Listener* gameListener, SDL_Renderer* renderer, SDL_Texture* spritesheet);

	void render(const SDL_Rect& viewport);

	void processMouseLocation(int x, int y);
	void processMouseClick(int x, int y);
	void processKeyPress(SDL_Keycode keycode);
};
