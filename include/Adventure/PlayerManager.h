#pragma once

#include "Adventure/Scene/ActorManager.h"
#include "Adventure/Scene/EffectManager.h"
#include "Entities/Actors/ActorEntity.h"
#include "Adventure/Scene/ItemManager.h"
#include "Entities/Actors/ActorUtils.h"
#include "Entities/Items/ItemFactory.h"
#include "Enums/PlayerCommands.h"
#include "EventListener/Listener.h"
#include "Logs/GameLog.h"
#include "Topography/LocalMap.h"
#include "Interface/InputConfirmer.h"
#include "Adventure/Scene/TurnQueue.h"


enum PlayerInputState {
	PLAYER_INPUT_MOVE,
	PLAYER_INPUT_LOOK,
	PLAYER_INPUT_SELECT
};

class PlayerManager : public Listener {
private:
	ActorEntity* player;
   void* playerArena;

	PlayerInputState inputState;

	LocalMap* map;
   TurnQueue* turnQueue;
   EffectManager* effectMan;
   ItemManager* itemMan;
   ItemFactory* itemFactory;
   ActorUtils* actorUtils;

   GameLog* gameLog;

	bool autoActing;
	PathingRoute autoMoveRoute;


public:
   PlayerManager(GameLog* gameLog);
   ~PlayerManager();

	//returns whether the turn needs to be run
	bool processDirectionalCommand(PlayerCommand command);
   void processClick(bool isRightClick);
   void processEvent(EventType event);

	ActorEntity* getPlayer();
	void placePlayer(TileCoords location);

	void updateInputState(PlayerCommand command);
   void lookAtMouseTile();
	bool doAutoAct();
	void clearAutoAct();
	void startAutoMove();
   bool isAutoActing();

   bool pickUpItem();
   void waitTurn();

   void setSceneDependencies(TurnQueue* queue, LocalMap* localMap, EffectManager* effectManager, ItemManager* itemManager, ItemFactory* itemFactory, ActorUtils* actorUtils);
};
