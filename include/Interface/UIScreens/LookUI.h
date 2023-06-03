#pragma once

#include "Entities/Actors/ActorDescriber.h"
#include "Entities/Effects/EffectDescriber.h"
#include "Entities/Items/ItemDescriber.h"
#include "GraphicsThings/TextRenderer.h"
#include "Adventure/Scene/Scene.h"
#include "GraphicsThings/TileDisplay.h"
#include <SDL.h>


class LookUI {
private:
	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

	LocalMap* map;

   GameTextMaker textMaker;
	TextRenderer textRenderer;
	TextRenderingSpecs textSpecs, textSpecsTitle;
   ActorDescriber actorDescriber;
   ItemDescriber itemDescriber;

   GameText titleText;
   GameText defaultText;

public:
	LookUI(int fontSize = 3) : map(nullptr), renderer(NULL), spritesheet(NULL),
   textSpecs(fontSize), textSpecsTitle(fontSize+1) {};

	void initialize(Scene* scene, SDL_Renderer* renderer, SDL_Texture* spritesheet);

	void render(Scene* scene, const SDL_Rect& viewport);
};
