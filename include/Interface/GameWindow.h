#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include "Adventure/Adventure.h"
#include "Topography/LocalMap.h"
#include "Logs/GameLog.h"
#include "UIScreens/AdventureUI.h"
#include "UIScreens/MessagesUI.h"
#include "UIScreens/MapUI.h"
#include "UIScreens/ConfirmerUI.h"
#include "UIScreens/PlayerUI.h"
#include "UIScreens/SceneUI.h"


class GameWindow {
private:
	SDL_Rect screenDimensions;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

   AdventureUI adventureUI;
	ConfirmerUI exitConfirmerUI;


	void resetRenderer();

public:
	GameWindow(Adventure* adventure, int windowWidth = 1600, int windowHeight = 1200);
	~GameWindow();

	bool initialize(InputConfirmer* inputSignaller, InputConfirmer* sceneSignaller);
	void update();

	void updateWindowDimensions(int width, int height);

	void processCursorLocation(int x, int y);
	void processClick(int x, int y, bool ctrlDown);
	void processScroll(int x, int y, int scrollOffset, bool ctrlDown);
	void processKeyPress(SDL_Keycode keycode);
};

#endif
