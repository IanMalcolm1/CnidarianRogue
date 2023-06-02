#pragma once

#include "Adventure/Scene/AIRunner.h"
#include "Adventure/Scene/EffectManager.h"
#include "Entities/Actors/ActorFactory.h"
#include "Entities/Actors/ActorUtils.h"
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

   TurnQueue turnQueue;

   ActorManager actorManager;
   ActorFactory actorFactory;
   ActorUtils actorUtils;
   AIRunner aiRunner;

   ItemManager itemManager;
   ItemFactory itemFactory;

   EffectManager effectManager;

	PathingRoute pathToMouseTile;

   PlayerManager* playerManager;
   GameLog* gameLog;


public:
	Scene(GameLog* gameLog, PlayerManager* playerManager) :
   map(150, 150), gameLog(gameLog), turnQueue(),
   actorManager(&turnQueue, &map, gameLog), 
   itemManager(&map), playerManager(playerManager),
   effectManager(&actorManager, &turnQueue),
   actorUtils(&actorManager, &itemManager, &effectManager),
   aiRunner(&map, &actorManager, &actorUtils),
   itemFactory(itemManager.makeFactory()),
   actorFactory(actorManager.makeFactory(&itemFactory)) {};

	LocalMap* getMap();
   ActorFactory* getActorFactory();
   TurnQueue* getTurnQueue();
   ItemManager* getItemManager();
   ItemFactory* getItemFactory();
   EffectManager* getEffectManager();
   ActorUtils* getActorUtils();

   void runTurn();
   void startAutoMove();
	void updateMapDisplay();
   void initialize();

	void setPlayerAt(TileCoords location);

   void hookupListeners(Listener* listener, Listener* listener1);
};
