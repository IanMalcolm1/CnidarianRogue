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
   Scene scene;
   TerrainGenerator terrainGenerator;
   GameLog log;
   PlayerManager playerMan;

   bool alreadyRanTurn;

   void linkPlayerAndScene();

public:
   Adventure() : log(GameLog()), scene(Scene(&log, &playerMan)),
   playerMan(PlayerManager(&log)), terrainGenerator(TerrainGenerator()),
   alreadyRanTurn(false) {
      linkPlayerAndScene();
	   terrainGenerator.rectangleRooms(&scene, 30, 30);
      scene.initialize();
      updateMapDisplay();
   };

   Scene* getScene();
   void changeScene();

   GameLog* getGameLog();
   PlayerManager* getPlayerManager();

	void processCommand(PlayerCommand command, Uint16 modification);

   void runTurnIfAutoMoving();
	void updateMapDisplay();

   void hookupListeners(Listener* listener);
};
