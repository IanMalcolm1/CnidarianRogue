#pragma once

#include <SDL.h>
#include "Adventure/Adventure.h"
#include "Adventure/PlayerManager.h"
#include "Adventure/Scene/Scene.h"
#include "Entities/Actors/ActorDescriber.h"
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
   ActorDescriber actorDescriber;

   GameText title, weaponTitle;

public:
	PlayerUI(int fontSize = 3) : playerMan(nullptr), renderer(NULL),
   spritesheet(NULL), textSpecsTitle(fontSize+1), textSpecs(fontSize) {};

	void initialize(Adventure* adventure, SDL_Renderer* renderer, SDL_Texture* spritesheet);

	void render(const SDL_Rect& viewport);
};
