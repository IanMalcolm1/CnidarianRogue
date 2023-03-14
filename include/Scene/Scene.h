#pragma once

#include "Topography/LocalMap.h"
#include "ActorPool.h"
#include "TurnQueue.h"
#include <SDL.h>
#include "UIScreens/InputConfirmer.h"
#include "PlayerManager/PlayerManager.h"


struct Scene {
private:
	LocalMap map;
	PlayerManager playerManager;
	ActorPool actorPool;
	TurnQueue turnQueue;

	PathingRoute pathToMouseTile;

	InputConfirmer confirmer;

	bool alreadyRanTurn;

	int performAction(Actor* actor);
	int testerLogic(Actor* actor);

	void runTurn();


public:
	Scene() : map(100, 100), actorPool(ActorPool()), turnQueue(TurnQueue()), 
		confirmer(InputConfirmer()), playerManager(PlayerManager()), alreadyRanTurn(false) {
		playerManager.initialize(&map, &confirmer, &turnQueue);
	};

	LocalMap* getMap();
	PlayerManager* getPlayerManager();
	InputConfirmer* presentConfirmationSignaller();

	void processCommand(PlayerCommand command, Uint16 modification);
	void updateMapDisplay();

	void setPlayerAt(TileCoords location);
	void createActorAt(TileCoords location);
	void destroyActor(Actor* actor);
	void moveActor(Actor* actor, TileCoords newLocation);

	void startAutoMove();
	void runTurnIfAutoMoving();
};
