#pragma once

#include <SDL.h>
#include "Adventure/PlayerManager.h"
#include "Interface/UIScreens/MapUI.h"
#include "Interface/UIScreens/MessagesUI.h"
#include "Interface/UIScreens/PlayerUI.h"
#include "Adventure/Scene/Scene.h"

class SceneUI {
private:
	Scene* scene;
   PlayerManager* playerMan;

	MapUI mapUI;

	SDL_Rect mapViewport;


public:
	bool hidden;

	SceneUI() : hidden(false), scene(nullptr), mapViewport({ 0,0,0,0 }),
   playerMan(nullptr) {};

	void initialize(PlayerManager* playerMan, SDL_Renderer* renderer, SDL_Texture* spritesheet);
   void cleanUp();

	void render(Scene* scene, const SDL_Rect& mapViewport);

	void processCursorLocation(int x, int y);
	void processScroll(int x, int y, int offset, bool isRightClick);
	void processClick(int x, int y, bool isRightClick);
};
