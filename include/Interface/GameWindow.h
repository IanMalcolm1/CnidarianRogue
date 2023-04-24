#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include "Topography/LocalMap.h"
#include "Logs/GameLog.h"
#include "UIScreens/MessagesUI.h"
#include "UIScreens/MapUI.h"
#include "UIScreens/ConfirmerUI.h"
#include "UIScreens/PlayerUI.h"
#include "UIScreens/SceneUI.h"


enum GameWindowState {
	WINDOW_STATE_MAP,
	WINDOW_STATE_MAIN_MENU,
	WINDOW_STATE_INVENTORY,
	WINDOW_STATE_CHARACTER_SHEET,
	EXIT_DIALOGUE
};

struct MapViewports {
	SDL_Rect map;
	SDL_Rect messages;
	SDL_Rect playerInfo;
};


class GameWindow {
private:
	GameWindowState state = WINDOW_STATE_MAP;

	SDL_Rect screenDimensions;
	MapViewports viewports;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

	SceneUI sceneUI;
	MessagesUI messagesUI;
	ConfirmerUI exitConfirmerUI;


	void renderScene();
	void renderRecentMessages();
	void renderExitConfirmer();

	void updateMapViewports();
	void resetRendererAndDrawBorder(SDL_Rect& currentViewport);

public:
	GameWindow(Scene* map, GameLog* log,
		int windowWidth = 1600, int windowHeight = 1200);
	~GameWindow();

	GameWindowState getState();
	void setState(GameWindowState state);

	bool initialize(InputConfirmer* inputSignaller, InputConfirmer* sceneSignaller);
	void update();

	void updateWindowDimensions(int width, int height);

	void processCursorLocation(int x, int y);
	void processClick(int x, int y, bool ctrlDown);
	void processScroll(int x, int y, int scrollOffset, bool ctrlDown);
	void processKeyPress(SDL_Keycode keycode);
};

#endif
