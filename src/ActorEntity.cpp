#include "Entities/Actors/ActorEntity.h"
#include "Entities/Actors/AI.h"

std::vector<TileCoords>* ActorEntity::getVisibleTiles() { return &visibleTiles; }
std::vector<ActorEntity*>* ActorEntity::getVisibleActors() { return &visibleActors; }

PathingRoute* ActorEntity::getCurrentRoute() { return &currentRoute; }

void ActorEntity::clearVisibilityArrays() {
	visibleTiles.clear();
	visibleActors.clear();
}
void ActorEntity::addVisibleTile(TileCoords tile) { visibleTiles.push_back(tile); }
void ActorEntity::addVisibleActor(ActorEntity* actor) { visibleActors.push_back(actor); }

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


bool ActorEntity::isAggroed() {
   AiStateId state = getState();
   return (state > AISTATE_ATTACKING && state < AISTATE_TOTAL_STATES);
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

void ActorEntity::checkForHostiles() {
   bool canSeeHostile = false;
   for (auto visibleActor : visibleActors) {
      if (isHostileTo(visibleActor)) {
         canSeeHostile = true;
         break;
      }
   }

   if (canSeeHostile && !isAggroed()) {
      setState(AISTATE_ATTACKING);
   }
   else if (!canSeeHostile && isAggroed()) {
      setState(AISTATE_IDLE);
   }
}

bool ActorEntity::isTargetting(ActorEntity *actor) {
   if (targetEntity && actor==targetEntity)
      return true;

   return false;
}

void ActorEntity::setTarget(ActorEntity* actor) {
   targetEntity = actor;
}

ActorEntity* ActorEntity::getTarget() {
   return targetEntity;
}

bool ActorEntity::canSeeTarget() {
   if (targetEntity == nullptr)
      return false;

   for (auto visibleActor : visibleActors) {
      if (visibleActor == targetEntity) {
         return true;
      }
   }
   return false;
}

void ActorEntity::chooseTarget() {
   for (auto visibleActor : visibleActors) {
      if (isHostileTo(visibleActor)) {
         setTarget(visibleActor);
      }
   }
}
      


void ActorEntity::reset() {
   isPlayer = false;
   display = TileDisplay();
   location = TileCoords();
   description.name = "ded entity";
   description.desc = "if you can see this there's a bug";
   naturalWeapon = nullptr;
   weapon = nullptr;
   faction = FACTION_PACIFIST;
   targetEntity = nullptr;
   visibleTiles.clear();
   visibleActors.clear();
   currentRoute.clear();

   Entity::reset();
}


ItemEntity* ActorEntity::getActiveWeapon() {
   if (!weapon) {
      return naturalWeapon;
   }
   else { return weapon; }
}

ItemEntity* ActorEntity::getHeldWeapon() {
   return weapon;
}

void ActorEntity::setNaturalWeapon(ItemEntity* natWeapon) {
   naturalWeapon = natWeapon;
}

void ActorEntity::setWeapon(ItemEntity* newWeapon) {
   weapon = newWeapon;
}

