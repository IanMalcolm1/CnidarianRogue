#pragma once


#include "Adventure/Adventure.h"
#include "SDL_render.h"
#include "Interface/UIScreens/MessagesUI.h"
#include "Interface/UIScreens/PlayerUI.h"
#include "Interface/UIScreens/SceneUI.h"
#include <locale>


struct AdventureViewports {
   SDL_Rect fullscreen;
	SDL_Rect map;
	SDL_Rect messages;
	SDL_Rect player;
};


class AdventureUI {
private:
   AdventureViewports viewports;

   SceneUI sceneUI;
   MessagesUI messagesUI;
   PlayerUI playerUI;

	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

   void updateViewports(const SDL_Rect& screenDimensions);
   void resetRendererAndDrawBorder(SDL_Rect& currentViewport);

public:
   AdventureUI(Adventure* adventure) :
   sceneUI(adventure->getScene()),
   messagesUI(adventure->getGameLog()),
   playerUI(adventure->getPlayerManager()),
   viewports() {};
   
	void initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet);
   void cleanUp();

	void render(const SDL_Rect& screenDimensions);

	void processCursorLocation(int x, int y);
	void processScroll(int x, int y, int offset, bool ctrlDown);
	void processClick(int x, int y, bool ctrlDown);
	void processKeyPress(SDL_Keycode keycode);
};
