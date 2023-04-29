#pragma once

#include "Algorithms/TerrainGenerators.h"
#include "Adventure/Scene/Scene.h"
#include "EventListener/Listener.h"
#include "Logs/GameLog.h"
#include "Adventure/PlayerManager.h"
#include "Interface/InputConfirmer.h"
#include <cwchar>


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
   };

   Scene* getScene();
   void changeScene();

   GameLog* getGameLog();
   PlayerManager* getPlayerManager();

	void processCommand(PlayerCommand command, Uint16 modification);

   void runTurnIfAutoMoving();
	void updateMapDisplay();

   void hookupInputManagerListener(Listener* listener);
};
