#pragma once

#include "Entities/Actors/ActorFactory.h"
#include "Entities/Items/ItemFactory.h"
#include "Adventure/Scene/ItemManager.h"
#include "Topography/LocalMap.h"
#include "Adventure/Scene/TurnQueue.h"
#include <SDL.h>
#include "Adventure/Scene/ActorManager.h"
#include "Adventure/PlayerManager.h"
#include "Logs/GameLog.h"


class Scene {
private:
	LocalMap map;

   ActorManager actorManager;
   ActorFactory actorFactory;

   ItemManager itemManager;
   ItemFactory itemFactory;

	PathingRoute pathToMouseTile;

   GameLog* gameLog;
   PlayerManager* playerManager;


public:
	Scene(GameLog* gameLog, PlayerManager* playerManager) :
      map(100, 100), gameLog(gameLog),
      actorManager(&map, gameLog), 
      itemManager(&map),
      playerManager(playerManager),
      actorFactory(actorManager.makeFactory()),
      itemFactory(itemManager.makeFactory()){};

	LocalMap* getMap();
   ActorFactory* getActorFactory();
   TurnQueue* getTurnQueue();
   ItemFactory* getItemFactory();

   void runTurn();
	void updateMapDisplay();

	void setPlayerAt(TileCoords location);

   void hookupInputManagerListener(Listener* listener);
};
