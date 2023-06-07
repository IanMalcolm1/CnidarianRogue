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

void SceneUI::processScroll(int x, int y, int offset) {
	mapUI.processScroll(x, y, offset);
}

void SceneUI::processClick(int x, int y, bool isRightClick) {
	SDL_Point point = { x,y };
	if (SDL_PointInRect(&point, &mapViewport)) {
	   mapUI.processCursorLocation(x, y);
      bool needToRunTurn = playerMan->processMouseClick(isRightClick);
      if (needToRunTurn) {
         scene->runTurn();
      }
	}
}
