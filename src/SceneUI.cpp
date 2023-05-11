#include "Interface/UIScreens/SceneUI.h"


void SceneUI::initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	mapUI.initialize(scene->getMap(), renderer, spritesheet);
}


void SceneUI::cleanUp() {
   mapUI.cleanUp();
}


void SceneUI::render(const SDL_Rect& mapViewport) {
	this->mapViewport = mapViewport;

	mapUI.render(mapViewport);
}

void SceneUI::processCursorLocation(int x, int y) {
	mapUI.processCursorLocation(x, y);
}

void SceneUI::processScroll(int x, int y, int offset, bool ctrlDown) {
	mapUI.processScroll(x, y, offset, ctrlDown);
}

void SceneUI::processClick(int x, int y, bool ctrlDown) {
	SDL_Point point = { x,y };
	if (SDL_PointInRect(&point, &mapViewport)) {
	   mapUI.processCursorLocation(x, y);
      if (ctrlDown) {
         playerMan->startAutoMove();
      }
      else {
         playerMan->lookAtMouseTile();
      }
	}
}
