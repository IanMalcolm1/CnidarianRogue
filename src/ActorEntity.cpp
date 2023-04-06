#include "Entities/ActorEntity.h"


std::vector<TileCoords>* ActorEntity::getVisibleTiles() { return &visibleTiles; }
std::vector<TileCoords>* ActorEntity::getVisibleActorLocations() { return &visibleActorLocations; }

PathingRoute* ActorEntity::getCurrentRoute() { return &currentRoute; }

void ActorEntity::clearVisibilityArrays() {
	visibleTiles.clear();
	visibleActorLocations.clear();
}
void ActorEntity::addVisibleTile(TileCoords tile) { visibleTiles.push_back(tile); }
void ActorEntity::addVisibleActorLocation(TileCoords location) { visibleActorLocations.push_back(location); }

AiStateId ActorEntity::getState() {
	auto stuff = ai.getState();
   bool stateChanged = stuff.first;
	if (stateChanged) {
		currentRoute.clear();
	}
	return stuff.second;
}

void ActorEntity::setState(AiStateId stateID) {
   ai.setState(stateID);
}

void ActorEntity::addIdleSubstate(AiState state) {
	ai.addIdleSubstate(state);
}
void ActorEntity::addAttackingSubstate(AiState state) {
	ai.addAttackingSubstate(state);
}
