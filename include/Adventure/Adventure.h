#pragma once

#include "Algorithms/TerrainGenerator.h"
#include "Adventure/Scene/Scene.h"
#include "EventListener/Listener.h"
#include "Logs/GameLog.h"
#include "Adventure/PlayerManager.h"
#include "Interface/InputConfirmer.h"
#include <cwchar>


class Adventure {
private:
   std::vector<Scene> scenes;
   Scene* scene;
   int sceneIndex;

   TerrainGenerator terrainGenerator;
   GameLog log;
   PlayerManager playerMan;

   bool alreadyRanTurn;

   void linkPlayerAndScene();
   void newScene();

public:
   Adventure() : log(GameLog()), sceneIndex(0), scene(nullptr),
   playerMan(PlayerManager(&log)), terrainGenerator(TerrainGenerator()),
   alreadyRanTurn(false), scenes(3, Scene(&log, &playerMan)) {};

   void initialize();

   Scene* getScene();

   GameLog* getGameLog();
   PlayerManager* getPlayerManager();

	void processCommand(PlayerCommand command, Uint16 modification);

   void runTurnIfAutoMoving();
	void updateMapDisplay();

   void hookupListeners(Listener* listener);
};
