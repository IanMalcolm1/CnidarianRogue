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
	LookUI(Scene* scene, int fontSize = 3) : map(scene->getMap()), renderer(NULL), spritesheet(NULL), textMaker(), textRenderer(), textSpecs(fontSize), textSpecsTitle(fontSize+1), defaultText(), actorDescriber(scene->getEffectManager()->getEffectDescriber()), itemDescriber(scene->getEffectManager()->getEffectDescriber()) {};

	void initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet);

	void render(const SDL_Rect& viewport);
};
