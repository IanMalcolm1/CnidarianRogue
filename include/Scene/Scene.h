#pragma once

#include "Entities/ActorFactory.h"
#include "Topography/LocalMap.h"
#include "TurnQueue.h"
#include <SDL.h>
#include "UIScreens/InputConfirmer.h"
#include "PlayerManager/PlayerManager.h"
#include "Scene/ActorManager.h"
#include "Logs/GameLog.h"


class Scene {
private:
	LocalMap map;

   ActorManager actorManager;
   ActorFactory actorFactory;

	PathingRoute pathToMouseTile;

	InputConfirmer confirmer;

   GameLog* gameLog;
   PlayerManager* playerManager;

	bool alreadyRanTurn;


public:
	Scene(GameLog* gameLog, PlayerManager* playerManager) :
      map(100, 100), alreadyRanTurn(false), gameLog(gameLog),
      confirmer(InputConfirmer()),
      actorManager(ActorManager(&map, gameLog)), 
      playerManager(playerManager),
      actorFactory(actorManager.makeFactory()) {};

	LocalMap* getMap();
   ActorFactory* getActorFactory();
   TurnQueue* getTurnQueue();

	InputConfirmer* presentConfirmationSignaller();

	void processCommand(PlayerCommand command, Uint16 modification);
	void updateMapDisplay();

	void setPlayerAt(TileCoords location);

   void startAutoMove();
   void runTurnIfAutoMoving();
};
