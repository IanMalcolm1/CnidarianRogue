#include "Entities/Actors/ActorEntity.h"
#include "Entities/Actors/AI.h"


bool ActorEntity::isPlayer() {
   return player;
}


/* For FOV */
void ActorEntity::clearVisibilityArrays() {
	visibleTiles.clear();
	visibleActors.clear();
}
void ActorEntity::addVisibleTile(TileCoords tile) { visibleTiles.push_back(tile); }
void ActorEntity::addVisibleActor(ActorEntity* actor) { visibleActors.push_back(actor); }



/* AI Stuff */
std::vector<TileCoords>* ActorEntity::getVisibleTiles() { return &visibleTiles; }
std::vector<ActorEntity*>* ActorEntity::getVisibleActors() { return &visibleActors; }

PathingRoute* ActorEntity::getCurrentRoute() { return &currentRoute; }
AiState ActorEntity::getState() {
	return aiState;
}

void ActorEntity::setState(AiState stateID) {
   if (stateID != aiState) {
      currentRoute.clear();
      aiState = stateID;
   }
}

bool ActorEntity::isAggroed() {
   return (aiState > AISTATE_ATTACKING && aiState < AISTATE_TOTAL_STATES);
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

bool ActorEntity::canSeeHostile() {
   bool canSeeHostile = false;
   for (auto visibleActor : visibleActors) {
      if (isHostileTo(visibleActor)) {
         canSeeHostile = true;
         break;
      }
   }
   return canSeeHostile;
}

bool ActorEntity::isTargetting(ActorEntity *actor) {
   if (targetEntity && actor==targetEntity)
      return true;

   return false;
}


ActorEntity* ActorEntity::getTarget() {
   return targetEntity;
}

TileCoords ActorEntity::getTargetLastKnownLocation() {
   return targetEntityLastLocation;
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

void ActorEntity::pickTarget() {
   if (canSeeTarget()) {
      setTarget(targetEntity);
      return;
   }

   else if (canSeeHostile()) {
      //pick random hostile for target
      for (auto visibleActor : visibleActors) {
         if (isHostileTo(visibleActor)) {
            setTarget(visibleActor);
         }
      }
   }

   //otherwise leave as is
}

void ActorEntity::setTarget(ActorEntity *actor) {
   targetEntity = actor;
   targetEntityLastLocation = targetEntity->location;
}



/* Meta */
void ActorEntity::reset() {
   display = EntityDisplay();
   location = TileCoords();
   description.name = "ded entity";
   description.desc = "if you're seeing this there's a bug";
   inventory = Inventory();
   faction = FACTION_PACIFIST;
   aiState = AISTATE_IDLE;
   targetEntity = nullptr;
   visibleTiles.clear();
   visibleActors.clear();
   currentRoute.clear();

   Entity::reset();
}
