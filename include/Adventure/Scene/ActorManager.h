#pragma once

/* Intent: Have a public method you call on an actor that gets the 
 * actor's state, and runs the corresponding logic function.
 * Logic functions will be private functions of this class */

#include "Entities/Actors/ActorDescriber.h"
#include "Entities/Actors/ActorEntity.h"
#include "Entities/Components.h"
#include "Entities/Damage.h"
#include "Entities/EntityColiseum.h"
#include "Adventure/Scene/TurnQueue.h"
#include "Adventure/Scene/EffectManager.h"
#include "Entities/Actors/ActorFactory.h"
#include "Entities/Items/ItemFactory.h"
#include "EventListener/Blabber.h"
#include "Topography/LocalMap.h"
#include "Logs/GameLog.h"
#include "Algorithms/Dice.h"


class ActorManager : public Blabber {
private:
   EntityColiseum<ActorEntity> actorColiseum;

   TurnQueue* turnQueue;
   LocalMap* map;
   GameLog* gameLog;

   Dice dice;

   std::string damageTypeNames[DAMAGE_NONE];

public:
   ActorManager(TurnQueue* turnQueue, LocalMap* map, GameLog* gameLog) :
      map(map), gameLog(gameLog), turnQueue(turnQueue), dice(),
      actorColiseum(EntityColiseum<ActorEntity>()) {
         damageTypeNames[DAMAGE_FIRE] = " </red:fire/>";
         damageTypeNames[DAMAGE_PHYSICAL] = "";
         damageTypeNames[DAMAGE_FROST] = " </lightblue:frost/>";
         damageTypeNames[DAMAGE_POISON] = " </green:poison/>";
      };

   void runActorTurns();

   void destroyActor(ActorEntity* actor);
   void addActorToTurnQueue(ActorEntity* actor, int turnTime);
   void moveActor(ActorEntity* actor, TileCoords newLocation);

   //When a class needs to damage an entity, it should use calcDamage
   // to decide what to print to the GameLog, then pass the amount of
   // damage into the damageActor function
   std::pair<int, std::string> calcDamage(ActorEntity* recipient, Damage damage);
   void damageActor(ActorEntity* actor, int damage);

   void sendMsgIfActorIsVisible(ActorEntity* actor, std::string message);

   ActorEntity* getActor(int id) {
      return actorColiseum.getEntity(id);
   };

   ActorFactory makeFactory(ItemFactory* itemFactory);
};
