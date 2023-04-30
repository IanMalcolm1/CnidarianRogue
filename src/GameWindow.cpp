#include "Interface/GameWindow.h"
#include "EventListener/Listener.h"
#include "Interface/UIScreens/ConfirmerUI.h"
#include "Interface/UIScreens/GameOverUI.h"
#include "Interface/UIScreens/PlayerUI.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

GameWindow::GameWindow(Adventure* adventure, int windowWidth, int windowHeight) :
adventureUI(adventure), exitConfirmerUI(4), gameOverUI(4) {
	screenDimensions.x = screenDimensions.y = 0;
	screenDimensions.w = windowWidth;
	screenDimensions.h = windowHeight;

	window = NULL;
	renderer = NULL;
	spritesheet = NULL;
}

GameWindow::~GameWindow() {
	printf("Window destructor called.\n");

   adventureUI.cleanUp();

	SDL_DestroyTexture(spritesheet);
	spritesheet = NULL;

   SDL_DestroyRenderer(renderer);
   renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}

bool GameWindow::initialize(Listener* gameListener) {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL didn't init. We're doomed. Error: %s\n", SDL_GetError());
		success = false;
	}
	if (IMG_Init(IMG_INIT_PNG) < 0) {
		printf("SDL_Image didn't innit. We're doomed. Error: %s\n", SDL_GetError());
		success = false;
	}

	window = SDL_CreateWindow(
		"A Simple Roguelike",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		screenDimensions.w, screenDimensions.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

	if (window == NULL) {
		printf("Couldn't make a window. Error: %s\n", SDL_GetError());
		success = false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	spritesheet = IMG_LoadTexture(renderer, "./assets/CGA8x8thin.png");
	if (spritesheet == NULL) {
		printf("Couldn't find spritesheet, I guess. Error: %s\n", IMG_GetError());
		success = false;
	}

	//UI screens
   adventureUI.initialize(renderer, spritesheet);
	exitConfirmerUI.initialize(gameListener, renderer, spritesheet);
   gameOverUI.initialize(gameListener, renderer, spritesheet);

	return success;
}


void GameWindow::resetRenderer() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetTextureAlphaMod(spritesheet, 255);
	SDL_SetTextureColorMod(spritesheet, 255, 255, 255);
}

void GameWindow::update() {
	SDL_RenderClear(renderer);

	adventureUI.render(screenDimensions);
   resetRenderer();

   gameOverUI.render(screenDimensions);
   resetRenderer();
   
	exitConfirmerUI.render(screenDimensions);
   resetRenderer();
   
	SDL_RenderPresent(renderer);
}


void GameWindow::updateWindowDimensions(int width, int height) {
	screenDimensions.w = width;
	screenDimensions.h = height;
}


void GameWindow::processCursorLocation(int x, int y) {
   if (!exitConfirmerUI.hidden) {
      exitConfirmerUI.processMouseLocation(x, y);
   }
   else if (!gameOverUI.hidden) {
      gameOverUI.processMouseLocation(x, y);
   }
   else {
      adventureUI.processCursorLocation(x, y);
   }
}

void GameWindow::processClick(int x, int y, bool ctrlDown) {
   if (!exitConfirmerUI.hidden) {
      exitConfirmerUI.processMouseClick(x,y);
   }
   else if (!gameOverUI.hidden) {
      gameOverUI.processMouseClick(x, y);
   }
   else {
      adventureUI.processClick(x, y, ctrlDown);
   }
}

void GameWindow::processScroll(int x, int y, int scrollOffset, bool ctrlDown) {
   adventureUI.processScroll(x, y, scrollOffset, ctrlDown);
}

void GameWindow::processKeyPress(SDL_Keycode keycode) {
   if (!exitConfirmerUI.hidden) {
      exitConfirmerUI.processKeyPress(keycode);
   }
   else if (!gameOverUI.hidden) {
      gameOverUI.processKeyPress(keycode);
   }
   else {
      adventureUI.processKeyPress(keycode);
   }
}


void GameWindow::processEvent(EventType event) {
   if (event == EVENT_PLAYERDED) {
      gameOverUI.hidden = false;
   }
}


void GameWindow::reset(Adventure* adventure, Listener* gameListener) {
   adventureUI = AdventureUI(adventure);
   adventureUI.initialize(renderer, spritesheet);

   exitConfirmerUI = ExitConfirmerUI(4);
	exitConfirmerUI.initialize(gameListener, renderer, spritesheet);

   gameOverUI = GameOverUI(4);
   gameOverUI.initialize(gameListener, renderer, spritesheet);
}


bool GameWindow::isShowingPopups() {
   return !(exitConfirmerUI.hidden && gameOverUI.hidden);
}

void GameWindow::showExitConfirmationPopup() {
   exitConfirmerUI.hidden = false;
}
