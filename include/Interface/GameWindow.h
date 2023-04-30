#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include "Adventure/Adventure.h"
#include "Interface/UIScreens/GameOverUI.h"
#include "Topography/LocalMap.h"
#include "Logs/GameLog.h"
#include "Interface/UIScreens/AdventureUI.h"
#include "Interface/UIScreens/MessagesUI.h"
#include "Interface/UIScreens/MapUI.h"
#include "Interface/UIScreens/ConfirmerUI.h"
#include "Interface/UIScreens/PlayerUI.h"
#include "Interface/UIScreens/SceneUI.h"


class GameWindow : public Listener {
private:
	SDL_Rect screenDimensions;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

   AdventureUI adventureUI;
	ConfirmerUI exitConfirmerUI;
   GameOverUI gameOverUI;

	void resetRenderer();

public:
	GameWindow(Adventure* adventure, int windowWidth = 1600, int windowHeight = 1200);
	~GameWindow();

	bool initialize(Listener* gameListener, InputConfirmer* inputSignaller, InputConfirmer* sceneSignaller);
	void update();

	void updateWindowDimensions(int width, int height);

	void processCursorLocation(int x, int y);
	void processClick(int x, int y, bool ctrlDown);
	void processScroll(int x, int y, int scrollOffset, bool ctrlDown);
	void processKeyPress(SDL_Keycode keycode);

   void reset(Adventure* adventure, Listener* gameListener, InputConfirmer* inputSignaller, InputConfirmer* sceneSignaller);

   void processEvent(EventType event);
};

#endif
