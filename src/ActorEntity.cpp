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
   if (ai.changeStateTo(stateID)) {
      currentRoute.clear();
   }
}

void ActorEntity::addIdleSubstate(AiState state) {
	ai.addIdleSubstate(state);
}
void ActorEntity::addAttackingSubstate(AiState state) {
	ai.addAttackingSubstate(state);
}


bool ActorEntity::isHostileTo(ActorEntity* actor) {
   if (faction == FACTION_BAD && actor->faction == FACTION_GOOD ||
         actor->faction == FACTION_PACIFIST)
      return true;
   
   else if (faction == FACTION_GOOD && actor->faction == FACTION_BAD)
      return true;

   else
      return false;
}

bool ActorEntity::isTargetting(ActorEntity *actor) {
   if (targetEntityId < 1)
      return false;

   if (actor->getId() == targetEntityId)
      return true;

   return false;
}


void ActorEntity::setTarget(ActorEntity* actor) {
   if (actor)
      targetEntityId = actor->getId();
   else
      targetEntityId = -1;
}


void ActorEntity::reset() {
   isPlayer = false;
   display = TileDisplay();
   location = TileCoords();
   description.desc = "ded";
   description.name = "ded entity";
   defaultAttack = DamagingComp();
   faction = FACTION_PACIFIST;
   targetEntityId = -1;
   visibleTiles.clear();
   visibleActorLocations.clear();
   currentRoute.clear();
   items.clear();

   Entity::reset();
}


std::vector<ItemEntity*>* ActorEntity::getItems() {
   return &items;
}
