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
#include "Topography/TileCoordinates.h"


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
	PathingRoute autoMoveRoute, selectionRoute;

   bool doAutoMovement(); //reurns true if turn should be run
	void startAutoMove(); //reurns true if turn should be run
   void lookAtMouseTile();
   
   TileCoords getNewLocation(TileCoords curr, PlayerCommand direction);

public:
   PlayerManager(GameLog* gameLog);
   ~PlayerManager();

	bool processDirectionalCommand(PlayerCommand command); //reurns true if turn should be run
   bool processMouseClick(bool isRightClick);
   void processEvent(EventType event);

	ActorEntity* getPlayer();
	void placePlayer(TileCoords location);

   void armPlayer();

	void updateInputState(PlayerCommand command);
   void resetInputState();
	bool doAutoAct();
	void clearAutoAct();
   bool isAutoActing(); //reurns true if turn should be run

   bool pickUpItem();
   void waitTurn();
   bool attemptLevelChange();
   bool processConfirm();

   void setSceneDependencies(TurnQueue* queue, LocalMap* localMap, EffectManager* effectManager, ItemManager* itemManager, ItemFactory* itemFactory, ActorUtils* actorUtils);
};
