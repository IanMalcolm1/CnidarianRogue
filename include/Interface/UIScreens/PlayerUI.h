#pragma once

#include <SDL.h>
#include "Adventure/PlayerManager.h"
#include "Adventure/Scene/Scene.h"
#include "Entities/Items/ItemDescriber.h"
#include "GraphicsThings/GameText.h"
#include "GraphicsThings/TextRenderer.h"

class PlayerUI {
private:
	PlayerManager* playerMan;

	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

   GameTextMaker textMaker;
	TextRenderer textRenderer;
	TextRenderingSpecs textSpecs, textSpecsTitle;
   ItemDescriber itemDescriber;

   GameText title, weaponTitle;

public:
	PlayerUI(PlayerManager* playerMan, Scene* scene, int fontSize = 3) : playerMan(playerMan), renderer(NULL), spritesheet(NULL), textMaker(), textRenderer(), textSpecs(fontSize), textSpecsTitle(fontSize+1), title(), weaponTitle(), itemDescriber(scene->getEffectManager()->getEffectDescriber()) {};

	void initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet);

	void render(const SDL_Rect& viewport);
};
