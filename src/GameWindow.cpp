#include "Interface/GameWindow.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

GameWindow::GameWindow(Scene* scene, GameLog* log,
	int windowWidth, int windowHeight) : sceneUI(scene), messagesUI(log),
	exitConfirmerUI(ConfirmerUI(4)) {
	screenDimensions.x = screenDimensions.y = 0;
	screenDimensions.w = windowWidth;
	screenDimensions.h = windowHeight;

	viewports.map.x = 1 * screenDimensions.w / 5;
	viewports.map.y = 0;
	viewports.map.h = 4 * screenDimensions.h / 5;
	viewports.map.w = 4 * screenDimensions.w / 5;

	updateMapViewports();

	window = NULL;
	renderer = NULL;
	spritesheet = NULL;
}

GameWindow::~GameWindow() {
	printf("Window destructor called.\n");

	SDL_DestroyTexture(spritesheet);
	spritesheet = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}

bool GameWindow::initialize(InputConfirmer* inputSignaller, InputConfirmer* sceneSignaller) {
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
		"Testing things out",
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
	sceneUI.initialize(renderer, spritesheet);
	messagesUI.initialize(renderer, spritesheet);
	exitConfirmerUI.initialize(inputSignaller, renderer, spritesheet);

	return success;
}


GameWindowState GameWindow::getState() { return state; }
void GameWindow::setState(GameWindowState state) { this->state = state; }


void GameWindow::renderRecentMessages() {
	messagesUI.render(viewports.messages);

	resetRendererAndDrawBorder(viewports.messages);
}

void GameWindow::renderExitConfirmer() {
	exitConfirmerUI.render(screenDimensions);
	resetRendererAndDrawBorder(screenDimensions);
}

void GameWindow::renderScene() {
	sceneUI.render(viewports.map, viewports.playerInfo);
	resetRendererAndDrawBorder(viewports.map);
	resetRendererAndDrawBorder(viewports.playerInfo);
}


void GameWindow::updateMapViewports() {
	int screenBorderSpacing = 5;
	int viewportSpacing = 8;

	/* x-axis */
	viewports.playerInfo.x = screenBorderSpacing;
	viewports.playerInfo.w = (1 * screenDimensions.w / 5) - (screenBorderSpacing + viewportSpacing/2);

	viewports.map.x = (1 * screenDimensions.w / 5) + (viewportSpacing/2);
	viewports.map.w = (4 * screenDimensions.w / 5) - (screenBorderSpacing + viewportSpacing/2);

	viewports.messages.x = (1 * screenDimensions.w / 5) + (viewportSpacing/2);
	viewports.messages.w = (4 * screenDimensions.w / 5) - (screenBorderSpacing + viewportSpacing/2);

	/* y-axis */
	viewports.playerInfo.y = screenBorderSpacing;
	viewports.playerInfo.h = screenDimensions.h - (2*screenBorderSpacing);

	viewports.map.y = screenBorderSpacing;
	viewports.map.h = (4 * screenDimensions.h / 5) - (screenBorderSpacing + viewportSpacing/2);

	viewports.messages.y = (4 * screenDimensions.h / 5) + (viewportSpacing/2);
	viewports.messages.h = (1 * screenDimensions.h / 5) - (screenBorderSpacing + viewportSpacing/2);
}


void GameWindow::resetRendererAndDrawBorder(SDL_Rect& currentViewport) {
	SDL_RenderSetViewport(renderer, &screenDimensions);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &currentViewport);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetTextureAlphaMod(spritesheet, 255);
	SDL_SetTextureColorMod(spritesheet, 255, 255, 255);
}


void GameWindow::update() {
	SDL_RenderClear(renderer);

	renderRecentMessages();
	renderScene();
	renderExitConfirmer();

	SDL_RenderPresent(renderer);
}


void GameWindow::updateWindowDimensions(int width, int height) {
	screenDimensions.w = width;
	screenDimensions.h = height;

	updateMapViewports();
}


void GameWindow::processCursorLocation(int x, int y) {
	exitConfirmerUI.processMouseLocation(x, y);
	sceneUI.processCursorLocation(x, y);
}

void GameWindow::processClick(int x, int y, bool ctrlDown) {
	exitConfirmerUI.processMouseClick(x,y);
	sceneUI.processClick(x, y, ctrlDown);
}

void GameWindow::processScroll(int x, int y, int scrollOffset, bool ctrlDown) {
	sceneUI.processScroll(x, y, scrollOffset, ctrlDown);
	messagesUI.processScroll(x, y, scrollOffset, ctrlDown);
}

void GameWindow::processKeyPress(SDL_Keycode keycode) {
	if (!exitConfirmerUI.hidden) {
		exitConfirmerUI.processKeyPress(keycode);
	}
	else {
		sceneUI.processKeyPress(keycode);
	}
}
