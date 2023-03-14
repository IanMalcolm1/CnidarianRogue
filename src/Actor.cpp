#include "GameObjects/Actor.h"


Item Actor::generateCorpse() {

	return Item();
}

void Actor::setLocation(TileCoords coordinates) {
	location = coordinates;
}

void Actor::setDisplay(TileDisplay* newDisplay) {
	display.copy(newDisplay);
}

TileCoords Actor::getLocation() { return location; }
void Actor::setPoolIndex(int index) { poolIndex = index; }
int Actor::getPoolIndex() { return poolIndex; }
TileDisplay* Actor::getDisplay() { return &display; }
StatBlock* Actor::getStats() { return &stats; }

std::vector<TileCoords>* Actor::getVisibleTiles() { return &visibleTiles; }
std::vector<TileCoords>* Actor::getVisibleActorLocations() { return &visibleActorLocations; }

PathingRoute* Actor::getCurrentRoute() { return &currentRoute; }

void Actor::clearVisibilityArrays() {
	visibleTiles.clear();
	visibleActorLocations.clear();
}
void Actor::addVisibleTile(TileCoords tile) { visibleTiles.push_back(tile); }
void Actor::addVisibleActorLocation(TileCoords location) { visibleActorLocations.push_back(location); }

AIStateID Actor::getState() {
	AIStateID newState = ai.getState(currentState);
	if (currentState != newState) {
		currentRoute.clear();
	}
	currentState = newState;
	return newState;
}

void Actor::setState(AIStateID stateID) {
	currentState = stateID;
}

void Actor::makePlayer() {
	player = true;
}

bool Actor::isPlayer() { return player;  }

void Actor::addIdleSubstate(AIState state) {
	ai.addIdleSubstate(state);
}
void Actor::addAttackingSubstate(AIState state) {
	ai.addAttackingSubstate(state);
}
