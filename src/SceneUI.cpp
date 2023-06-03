#include "Interface/UIScreens/SceneUI.h"


void SceneUI::initialize(PlayerManager* playerMan, SDL_Renderer* renderer, SDL_Texture* spritesheet) {
   this->playerMan = playerMan;
	mapUI.initialize(renderer, spritesheet);
}


void SceneUI::cleanUp() {
   mapUI.cleanUp();
}


void SceneUI::render(Scene* scene, const SDL_Rect& mapViewport) {
	this->mapViewport = mapViewport;
   this->scene = scene;

	mapUI.render(scene->getMap(), mapViewport);
}

void SceneUI::processCursorLocation(int x, int y) {
	mapUI.processCursorLocation(x, y);
}

void SceneUI::processScroll(int x, int y, int offset, bool isRightClick) {
	mapUI.processScroll(x, y, offset, isRightClick);
}

void SceneUI::processClick(int x, int y, bool isRightClick) {
	SDL_Point point = { x,y };
	if (SDL_PointInRect(&point, &mapViewport)) {
	   mapUI.processCursorLocation(x, y);
      if (isRightClick) {
         playerMan->lookAtMouseTile();
      }
      else {
         scene->startAutoMove();
      }
	}
}
