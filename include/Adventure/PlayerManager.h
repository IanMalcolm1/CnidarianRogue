#pragma once

#include "Entities/ActorEntity.h"
#include "Enums/PlayerCommands.h"
#include "Topography/LocalMap.h"
#include "Interface/InputConfirmer.h"
#include "Adventure/Scene/TurnQueue.h"


enum PlayerInputState {
	PLAYER_INPUT_MOVE,
	PLAYER_INPUT_LOOK,
	PLAYER_INPUT_SELECT
};

class PlayerManager {
private:
	ActorEntity* player;
   void* playerArena;

	PlayerInputState inputState;

	LocalMap* map;
   TurnQueue* turnQueue;

	InputConfirmer* confirmer;

	PathingRoute autoMoveRoute;


public:
	bool autoActing;

   PlayerManager();
   ~PlayerManager();

	//returns whether the turn needs to be run
	bool processDirectionalCommand(PlayerCommand command);
   void processClick(bool ctrlDown);

	ActorEntity* getPlayer();
	void placePlayer(TileCoords location);

	void updateInputState(PlayerCommand command);
   void lookAtMouseTile();
	bool doAutoAct();
	void clearAutoAct();
	void startAutoMove();

   void waitTurn();

   void setSceneDependencies(TurnQueue* queue, LocalMap* localMap);
};
