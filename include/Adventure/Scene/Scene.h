#pragma once

#include "Adventure/Scene/AIRunner.h"
#include "Adventure/Scene/EffectManager.h"
#include "Entities/Abilities/AbilityManager.h"
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

   AbilityManager abilityManager;

	PathingRoute pathToMouseTile;

   PlayerManager* playerManager;
   GameLog* gameLog;


public:
	Scene(GameLog* gameLog, PlayerManager* playerManager, int mapWidth = 96,
   int mapHeight = 96) : map(mapWidth, mapHeight), gameLog(gameLog),
   playerManager(playerManager) {};

   void initialize(EffectDescriber* effectDescriber);

	LocalMap* getMap();
   ActorFactory* getActorFactory();
   TurnQueue* getTurnQueue();
   ItemManager* getItemManager();
   ItemFactory* getItemFactory();
   EffectManager* getEffectManager();
   EffectDescriber* getEffectDescriber();
   ActorUtils* getActorUtils();
   AbilityManager* getAbilityManager();
   ActorManager* getActorManager();

   void runTurn();
	void updateMapDisplay();

	void setPlayerAt(TileCoords location);

   void hookupListeners(Listener* listener, Listener* listener1);
};
