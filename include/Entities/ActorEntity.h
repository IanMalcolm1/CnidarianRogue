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
	std::vector<ActorEntity*> visibleActors;
	PathingRoute currentRoute;
   ActorEntity* targetEntity;

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
      targetEntity(nullptr) {};

   void reset();

   std::vector<ItemEntity*>* getItems();

	std::vector<TileCoords>* getVisibleTiles();
	std::vector<ActorEntity*>* getVisibleActors();
	PathingRoute* getCurrentRoute();

   void setFaction(Faction newFaction);
   bool isHostileTo(ActorEntity* actor);
   void checkForHostiles();
   bool isTargetting(ActorEntity* actor);
   void setTarget(ActorEntity* actor);
   ActorEntity* getTarget();
   bool canSeeTarget();
   void chooseTarget();

	void clearVisibilityArrays();
	void addVisibleTile(TileCoords tile);
	void addVisibleActor(ActorEntity* actor);

	void addIdleSubstate(AiState state);
	void addAttackingSubstate(AiState state);
   bool isAggroed();
	AiStateId getState();
	void setState(AiStateId stateID);
};
