#include "UIScreens/SceneUI.h"


void SceneUI::initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	confirmerUI.initialize(scene->getInputConfirmer(), renderer, spritesheet);
	mapUI.initialize(scene->getMap(), renderer, spritesheet);
}

void SceneUI::render(const SDL_Rect& mapViewport) {
	this->mapViewport = mapViewport;

	mapUI.render(mapViewport);
	confirmerUI.render(mapViewport);
}

void SceneUI::processCursorLocation(int x, int y) {
	confirmerUI.processMouseLocation(x, y);
	mapUI.processCursorLocation(x, y);
}

void SceneUI::processScroll(int x, int y, int offset, bool ctrlDown) {
	mapUI.processScroll(x, y, offset, ctrlDown);
}

void SceneUI::processClick(int x, int y, bool ctrlDown) {
	SDL_Point point = { x,y };
	if (ctrlDown && SDL_PointInRect(&point, &mapViewport)) {
		x -= mapViewport.x;
		y -= mapViewport.y;

		scene->startAutoMove();
	}
}

void SceneUI::processKeyPress(SDL_Keycode keycode) {
	confirmerUI.processKeyPress(keycode);
}
