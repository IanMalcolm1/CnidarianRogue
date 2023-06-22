#pragma once

#include <SDL.h>
#include "Adventure/Adventure.h"
#include "Adventure/PlayerManager.h"
#include "Adventure/Scene/Scene.h"
#include "Entities/Actors/ActorDescriber.h"
#include "Entities/Items/ItemDescriber.h"
#include "GraphicsThings/GameText.h"
#include "GraphicsThings/TextRenderer.h"
#include "Interface/UIScreens/Scroller.h"

class PlayerUI {
private:
	PlayerManager* playerMan;

	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

   Scroller scroller;
   GameTextMaker textMaker;
	TextRenderingSpecs textSpecs, textSpecsTitle;
   ItemDescriber itemDescriber;
   ActorDescriber actorDescriber;

   GameText title, statsTitle, weaponTitle, armorTitle;

public:
	PlayerUI(int fontSize = 2) : playerMan(nullptr), renderer(NULL),
   spritesheet(NULL), textSpecsTitle(fontSize+1), textSpecs(fontSize) {};

	void initialize(Adventure* adventure, SDL_Renderer* renderer, SDL_Texture* spritesheet);

	void render(const SDL_Rect& viewport);

   void processScroll(int x, int y, int offset, bool ctrlDown);
};
