#include "Game.h"
#include "Adventure/Adventure.h"
#include "EventListener/Listener.h"
#include "Logs/DebugLogger.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <memory>


Game::Game() {
	isRunning = false;
	millisecsPrevFrame = 0;

	adventure = std::make_unique<Adventure>();

	gameWindow = std::make_unique<GameWindow>(adventure.get());

	inputManager = std::make_unique<InputManager>(gameWindow.get(), adventure.get());

	printf("Game constructor called.\n");
}

Game::~Game() {
	printf("Game destructor called.\n");
   DebugLogger::closeDebugLogger();
}

bool Game::Initialize() {
	isRunning = true;
	bool success;


	InputConfirmer* inputConfirmer = inputManager->getInputConfirmer();
	InputConfirmer* adventureConfirmer = adventure->getScene()->getInputConfirmer();
	success = gameWindow->initialize(inputConfirmer, adventureConfirmer);

   adventure->hookupInputManagerListener((Listener*) inputManager.get());

	return success;
}

void Game::Run() {
	while (isRunning) {
		//wasting time between frames
		int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPrevFrame);
		if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
			SDL_Delay(timeToWait);
		}

		Update();

		millisecsPrevFrame = SDL_GetTicks();
	}
}


void Game::Update() {
	gameWindow->update();

	isRunning = inputManager->processInput();

	adventure->runTurnIfAutoMoving();
	adventure->updateMapDisplay();
}
