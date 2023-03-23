#pragma once

#include "GameObjects/Actor.h"
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
	Actor player;

	PlayerInputState inputState;

	LocalMap* map;
   TurnQueue* turnQueue;

	InputConfirmer* sceneConfirmer;

	PathingRoute autoMoveRoute;


public:
	bool autoActing;

	PlayerManager(TurnQueue* turnQueue) : player(Actor()), turnQueue(turnQueue), inputState(PLAYER_INPUT_MOVE), map(nullptr),
		sceneConfirmer(nullptr), autoActing(false) {};

	void initialize(LocalMap* map, InputConfirmer* sceneConfirmer);

	//returns whether the turn needs to be run
	bool processDirectionalCommand(PlayerCommand command);

	Actor* getPlayer();
	void placePlayer(TileCoords location);

	void updateInputState(PlayerCommand command);
	bool doAutoAct();
	void clearAutoAct();
	void startAutoMove();
};
