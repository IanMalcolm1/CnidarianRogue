#pragma once

#include "Entities/ActorEntity.h"
#include "Enums/PlayerCommands.h"
#include "Topography/LocalMap.h"
#include "UIScreens/InputConfirmer.h"
#include "Scene/TurnQueue.h"


enum PlayerInputState {
	PLAYER_INPUT_MOVE,
	PLAYER_INPUT_LOOK,
	PLAYER_INPUT_SELECT
};

class PlayerManager {
private:
	ActorEntity* player;

	PlayerInputState inputState;

	LocalMap* map;
   TurnQueue* turnQueue;

	InputConfirmer* sceneConfirmer;

	PathingRoute autoMoveRoute;


public:
	bool autoActing;

	PlayerManager(TurnQueue* queue, LocalMap* map, InputConfirmer* sceneConfirmer) :
      turnQueue(queue), player(nullptr), map(map),
      inputState(PLAYER_INPUT_MOVE), autoActing(false), 
		sceneConfirmer(sceneConfirmer) {};

	void initialize(ActorEntity* player);

	//returns whether the turn needs to be run
	bool processDirectionalCommand(PlayerCommand command);

	ActorEntity* getPlayer();
	void placePlayer(TileCoords location);

	void updateInputState(PlayerCommand command);
	bool doAutoAct();
	void clearAutoAct();
	void startAutoMove();
};
