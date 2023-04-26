#pragma once

#include <SDL.h>
#include "Interface/UIScreens/MapUI.h"
#include "Interface/UIScreens/MessagesUI.h"
#include "Interface/UIScreens/PlayerUI.h"
#include "Interface/UIScreens/ConfirmerUI.h"
#include "Adventure/Scene/Scene.h"

class SceneUI {
private:
	Scene* scene;

	MapUI mapUI;
	ConfirmerUI confirmerUI;

	SDL_Rect mapViewport;


public:
	bool hidden;

	SceneUI(Scene* scene) : hidden(false), mapUI(MapUI()),
		confirmerUI(ConfirmerUI(3)), scene(scene),
      mapViewport({ 0,0,0,0 }) {};

	void initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet);

	void render(const SDL_Rect& mapViewport);

	void processCursorLocation(int x, int y);
	void processScroll(int x, int y, int offset, bool ctrlDown);
	void processClick(int x, int y, bool ctrlDown);
	void processKeyPress(SDL_Keycode keycode);
};
