#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include "Adventure/Adventure.h"
#include "Interface/UIScreens/FpsUI.h"
#include "Interface/UIScreens/GameOverUI.h"
#include "Topography/LocalMap.h"
#include "Logs/GameLog.h"
#include "Interface/UIScreens/AdventureUI.h"
#include "Interface/UIScreens/MessagesUI.h"
#include "Interface/UIScreens/MapUI.h"
#include "Interface/UIScreens/ExitConfirmerUI.h"
#include "Interface/UIScreens/PlayerUI.h"
#include "Interface/UIScreens/SceneUI.h"


class GameWindow : public Listener {
private:
	SDL_Rect screenDimensions;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

   AdventureUI adventureUI;
	ExitConfirmerUI exitConfirmerUI;
   GameOverUI gameOverUI;
   FpsUI fpsUI;

	void resetRenderer();

public:
	GameWindow(Adventure* adventure, int windowWidth = 800, int windowHeight = 400);
	~GameWindow();

	bool initialize(Listener* gameListener);
	void update(int fps);

	void updateWindowDimensions(int width, int height);

	void processCursorLocation(int x, int y);
   void processCursorMovement();
	void processClick(int x, int y, bool isRightClick);
	void processScroll(int x, int y, int scrollOffset, bool ctrlDown);
	void processKeyPress(SDL_Keycode keycode, SDL_Keymod modification);

   void reset(Adventure* adventure, Listener* gameListener);

   void processEvent(EventType event);

   bool isShowingPopups();
   void showExitConfirmationPopup();
};

#endif
