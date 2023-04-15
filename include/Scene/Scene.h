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
	PlayerManager playerManager;

	PathingRoute pathToMouseTile;

	InputConfirmer confirmer;

   GameLog* gameLog;

	bool alreadyRanTurn;


public:
	Scene(GameLog* gameLog) : map(100, 100),
      alreadyRanTurn(false), gameLog(gameLog),
      confirmer(InputConfirmer()),
      actorManager(ActorManager(&map, gameLog)), 
		playerManager(PlayerManager(actorManager.getTurnQueue(), &map, &confirmer)),
      actorFactory(actorManager.makeFactory()) {
		   playerManager.initialize(actorFactory.makePlayer());
	};

	LocalMap* getMap();
	PlayerManager* getPlayerManager();
   ActorFactory* getActorFactory();

	InputConfirmer* presentConfirmationSignaller();

	void processCommand(PlayerCommand command, Uint16 modification);
	void updateMapDisplay();

	void setPlayerAt(TileCoords location);

   void startAutoMove();
   void runTurnIfAutoMoving();
};
