#pragma once

#include "Algorithms/TerrainGenerators.h"
#include "Adventure/Scene/Scene.h"
#include "Logs/GameLog.h"
#include "Adventure/PlayerManager.h"
#include "Interface/UIScreens/InputConfirmer.h"


class Adventure {
private:
   Scene scene;
   TerrainGenerators terrainGenerator;
   GameLog log;
   PlayerManager playerMan;

   void linkPlayerAndScene();

public:
   Adventure() : log(GameLog()), scene(Scene(&log, &playerMan)),
   playerMan(PlayerManager()), terrainGenerator(TerrainGenerators()) {
      linkPlayerAndScene();
	   terrainGenerator.rectangleRooms(&scene, 20, 20);
      updateMapDisplay();
      log.sendMessage("Test");
   };


   Scene* getScene();
   void changeScene();

   GameLog* getGameLog();
   PlayerManager* getPlayerManager();

	void processCommand(PlayerCommand command, Uint16 modification);

   void runTurnIfAutoMoving();
	void updateMapDisplay();
};
