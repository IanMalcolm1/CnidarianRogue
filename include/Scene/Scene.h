#pragma once

#include "GameObjects/TileCoordinates.h"
#include "Topography/LocalMap.h"
#include "ActorPool.h"
#include "TurnQueue.h"
#include <SDL.h>
#include "UIScreens/InputConfirmer.h"
#include "PlayerManager/PlayerManager.h"
#include "Scene/ActorManager.h"


class Scene {
private:
	LocalMap map;
	PlayerManager playerManager;
	TurnQueue turnQueue;
   ActorManager actorManager;

	PathingRoute pathToMouseTile;

	InputConfirmer confirmer;

	bool alreadyRanTurn;


public:
	Scene() : map(100, 100), turnQueue(TurnQueue()),
		confirmer(InputConfirmer()), playerManager(PlayerManager(&turnQueue)),
      alreadyRanTurn(false), actorManager(ActorManager(&map, &turnQueue)) {
		playerManager.initialize(&map, &confirmer);
	};

	LocalMap* getMap();
	PlayerManager* getPlayerManager();
	InputConfirmer* presentConfirmationSignaller();

	void processCommand(PlayerCommand command, Uint16 modification);
	void updateMapDisplay();

	void setPlayerAt(TileCoords location);
   void createActorAt(TileCoords location);

   void startAutoMove();
   void runTurnIfAutoMoving();
};
