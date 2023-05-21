#pragma once

#include "GraphicsThings/TextRenderer.h"
#include "Adventure/Scene/Scene.h"
#include "GraphicsThings/TileDisplay.h"
#include <SDL.h>


class LookUI {
private:
	LocalMap* map;

	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

   GameTextMaker textMaker;
	TextRenderer textRenderer;
	TextRenderingSpecs textSpecs, textSpecsTitle;

   GameText titleText;
   GameText defaultText;

   GameText makeName(std::string name, EntityDisplay disp);

public:
	LookUI(Scene* scene, int fontSize = 3) : map(scene->getMap()), renderer(NULL), spritesheet(NULL), textMaker(), textRenderer(), textSpecs(fontSize), textSpecsTitle(fontSize+1), defaultText() {};

	void initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet);

	void render(const SDL_Rect& viewport);
};
