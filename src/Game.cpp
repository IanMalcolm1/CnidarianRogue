#include "Game.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <memory>


Game::Game() {
	isRunning = false;
	millisecsPrevFrame = 0;

	gameLog = std::make_unique<GameLog>();
	gameLog->sendMessage("Hi, I'm </000255000:Ian/>. Te</000255000:eeeeeeeee/>est. Another </red:test/>. Now I have more </lightblue:colors/>!");
	gameLog->sendMessage("</red:Message 2. Going to make this reeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaallllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllly loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong!!!!!!!!!!!!!!!!!!/>");
	gameLog->sendMessage("</orange:Message 3/>");
	gameLog->sendMessage("</yellow:Message 4/>");
	gameLog->sendMessage("</green:Message 5/>");
	gameLog->sendMessage("</blue:Message 6/>");
	gameLog->sendMessage("</purple:Message 7/>");
	gameLog->sendMessage("</gold:The golden message/>");

	terrainGenerator = TerrainGenerators();

	scene = std::make_unique<Scene>(gameLog.get());

	gameWindow = std::make_unique<GameWindow>(scene.get(), gameLog.get());

	inputManager = std::make_unique<InputManager>(gameWindow.get(), scene.get());

	printf("Game constructor called.\n");
}

Game::~Game() {
	printf("Game destructor called.\n");
}

bool Game::Initialize() {
	isRunning = true;
	bool success;

	terrainGenerator.rectangleRooms(scene.get(), 20, 20);

	InputConfirmer* inputConfirmer = inputManager->presentConfirmer();
	InputConfirmer* sceneConfirmer = scene->presentConfirmationSignaller();
	success = gameWindow->initialize(inputConfirmer, sceneConfirmer);

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

	scene->runTurnIfAutoMoving();
	scene->updateMapDisplay();
}
