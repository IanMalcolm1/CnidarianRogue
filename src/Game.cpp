#include "Game.h"
#include "Adventure/Adventure.h"
#include "Algorithms/FpsCounter.h"
#include "EventListener/Listener.h"
#include "Logs/DebugLogger.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <memory>


Game::Game() {
	isRunning = false;
   needsToDie = false;
   needToRestart = false;
	millisecsPrevFrame = 0;

   fpsCounter = FpsCounter();

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
   srand(time(0));

	isRunning = true;
	bool success;

   adventure->initialize();

	success = gameWindow->initialize((Listener*)this);

   adventure->hookupListeners((Listener*) gameWindow.get());

	return success;
}

void Game::Run() {
	while (isRunning && !needsToDie) {
		//wasting time between frames
		int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPrevFrame);
		if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
			SDL_Delay(timeToWait);
		}

      fpsCounter.markStartPoint();
		Update();
      fpsCounter.markEndPoint();

		millisecsPrevFrame = SDL_GetTicks();
	}

   if (needToRestart) {
      restart();
   }
}


void Game::Update() {
	gameWindow->update(fpsCounter.getAverageFps());

	isRunning = inputManager->processInput();

	adventure->runTurnIfAutoMoving();
	adventure->updateMapDisplay();
}


void Game::restart() {
   adventure.reset();
   adventure = std::make_unique<Adventure>();

   inputManager.reset();
   inputManager = std::make_unique<InputManager>(gameWindow.get(), adventure.get());

   gameWindow->reset(adventure.get(), (Listener*)this);

   adventure->hookupListeners((Listener*) gameWindow.get());

   needToRestart = false;
   needsToDie = false;

   Run();
}


void Game::processEvent(EventType event) {
   if (event == EVENT_QUIT_GAME) {
      needsToDie = true;
   }
   else if (event == EVENT_RESTART_GAME) {
      needsToDie = true;
      needToRestart = true;
   }
}
