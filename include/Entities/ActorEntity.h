#pragma once

#include "AI.h"
#include "Entities/Ability.h"
#include "Entities/Components.h"
#include "Entities/ItemEntity.h"
#include "GraphicsThings/TileDisplay.h"
#include "Enums/TurnTime.h"
#include "Algorithms/PathfindingRoute.h"
#include "Entities/ActorStatBlock.h"
#include <cwchar>

enum Faction {
   FACTION_GOOD,
   FACTION_BAD,
   FACTION_PACIFIST
};

class ActorEntity : public Entity {
private:
	AI ai;

	std::vector<TileCoords> visibleTiles;
	std::vector<TileCoords> visibleActorLocations;
	PathingRoute currentRoute;
   int targetEntityId;

	//std::vector<Ability> abilities; (unimplemented)
	std::vector<ItemEntity*>  items;

public:
	bool isPlayer;

	ActorStatBlock stats;
	TileDisplay display;
	TileCoords location;
   Description description;
   DamagingComp defaultAttack;
   Faction faction;


	ActorEntity(int id, int bytesUsed, int totalSpace)
      : Entity(id, bytesUsed, totalSpace), location(TileCoords()),
      display(TileDisplay()), ai(AI()), isPlayer(false),
      targetEntityId(-1) {};

   void reset();

   std::vector<ItemEntity*>* getItems();

	std::vector<TileCoords>* getVisibleTiles();
	std::vector<TileCoords>* getVisibleActorLocations();
	PathingRoute* getCurrentRoute();

   void setFaction(Faction newFaction);
   bool isHostileTo(ActorEntity* actor);
   bool isTargetting(ActorEntity* actor);
   void setTarget(ActorEntity* actor);

	void clearVisibilityArrays();
	void addVisibleTile(TileCoords tile);
	void addVisibleActorLocation(TileCoords location);

	void addIdleSubstate(AiState state);
	void addAttackingSubstate(AiState state);
	AiStateId getState();
	void setState(AiStateId stateID);
};
