#pragma once

#include "Entities/Abilities/Ability.h"
#include "Entities/Actors/AI.h"
#include "Entities/Actors/Inventory.h"
#include "Entities/Components.h"
#include "Entities/Effects/EffectList.h"
#include "Entities/Items/ItemEntity.h"
#include "GraphicsThings/TileDisplay.h"
#include "Enums/TurnTime.h"
#include "Algorithms/PathfindingRoute.h"
#include "Entities/Actors/ActorStatBlock.h"
#include <cwchar>

enum Faction {
   FACTION_GOOD,
   FACTION_BAD,
   FACTION_PACIFIST
};

class ActorEntity : public Entity {
private:
	bool player;

   AiState aiState;
	std::vector<TileCoords> visibleTiles;
	std::vector<ActorEntity*> visibleActors;
	PathingRoute currentRoute;
   ActorEntity* targetEntity;
   TileCoords targetEntityLastLocation;


public:
   AiType aiType;
   Inventory inventory;
   EffectList activeEffects;
	ActorStatBlock stats;
	EntityDisplay display;
	TileCoords location;
   Description description;
   Faction faction;
   Ability ability;


	ActorEntity(int id, int bytesUsed, int totalSpace, bool player = false)
   : Entity(id, bytesUsed, totalSpace), location(TileCoords()),
   display(EntityDisplay()), player(player), targetEntity(nullptr),
   aiState(AISTATE_IDLE) {};

   void reset();

   bool isPlayer();

	std::vector<TileCoords>* getVisibleTiles();
	std::vector<ActorEntity*>* getVisibleActors();
	PathingRoute* getCurrentRoute();

   void setFaction(Faction newFaction);
   bool isHostileTo(ActorEntity* actor);

   void setTarget(ActorEntity* actor);
   bool canSeeHostile();
   bool isTargetting(ActorEntity* actor);
   void pickTarget();
   ActorEntity* getTarget();
   TileCoords getTargetLastKnownLocation();
   bool canSeeTarget();

	void clearVisibilityArrays();
	void addVisibleTile(TileCoords tile);
	void addVisibleActor(ActorEntity* actor);

   bool isAggroed();
   AiState getState();
	void setState(AiState stateID);
};
