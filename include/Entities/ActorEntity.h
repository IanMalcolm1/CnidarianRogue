#pragma once

#include "AI.h"
#include "Entities/Ability.h"
#include "Entities/ItemEntity.h"
#include "GraphicsThings/TileDisplay.h"
#include "Enums/TurnTime.h"
#include "Algorithms/PathfindingRoute.h"
#include "Entities/ActorStatBlock.h"


class ActorEntity : public Entity {
private:
	AI ai;

	std::vector<TileCoords> visibleTiles;
	std::vector<TileCoords> visibleActorLocations;
	PathingRoute currentRoute;

	//std::vector<Ability> abilities; (unimplemented)
	std::vector<ItemEntity*>  items;

public:
	bool isPlayer = false;

	ActorStatBlock stats;
	TileDisplay display;
	TileCoords location;
   Description description;


	ActorEntity(int id, int bytesUsed, int totalSpace)
      : Entity(id, bytesUsed, totalSpace), location(TileCoords()),
      display(TileDisplay()), ai(AI()), isPlayer(false) {};

	std::vector<TileCoords>* getVisibleTiles();
	std::vector<TileCoords>* getVisibleActorLocations();
	PathingRoute* getCurrentRoute();

	void clearVisibilityArrays();
	void addVisibleTile(TileCoords tile);
	void addVisibleActorLocation(TileCoords location);

	void addIdleSubstate(AiState state);
	void addAttackingSubstate(AiState state);
	AiStateId getState();
	void setState(AiStateId stateID);
};
