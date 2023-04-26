#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "Adventure/Adventure.h"
#include "Interface/GameWindow.h"
#include "Adventure/Scene/Scene.h"
#include "Interface/InputManager.h"
#include "Algorithms/TerrainGenerators.h"
#include "Logs/GameLog.h"


const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game {
private:
	//game loop
	bool isRunning;
	int millisecsPrevFrame;

	std::unique_ptr<GameWindow> gameWindow;
	std::unique_ptr<InputManager> inputManager;
	std::unique_ptr<Adventure> adventure;

public:
	Game();
	~Game();
	bool Initialize();
	void Run();
	void Update();
};

#endif
