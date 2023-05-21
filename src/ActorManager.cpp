#include "Adventure/Scene/ActorManager.h"
#include "Algorithms/Dice.h"
#include "Entities/Actors/AI.h"
#include "Algorithms/FoV.h"
#include "Algorithms/Pathfinding.h"
#include "Entities/Actors/ActorFactory.h"
#include "Adventure/Scene/TurnQueue.h"
#include "Entities/Components.h"
#include "EventListener/Listener.h"
#include <cwchar>
#include <random>
#include <string>


void ActorManager::destroyActor(ActorEntity* actor) {
	map->setActorAt(actor->location, nullptr);
	turnQueue->removeActor(actor);

   map->addItemAt(actor->location, actor->getHeldWeapon());

   if (actor->isPlayer()) {
      notifyListeners(EVENT_PLAYERDED);
      turnQueue->insertActor(actor, 0);
      return;
   }

   for (int i=0; i<actorColiseum.getDirtySlots(); i++) {
      if (actorColiseum.getEntity(i)->isTargetting(actor)) {
         actorColiseum.getEntity(i)->setTarget(NULL);
      }
   }

   actorColiseum.deleteEntity(actor->getId());
}

void ActorManager::moveActor(ActorEntity* actor, TileCoords newLocation) {
   map->setActorAt(actor->location, nullptr);
   actor->location = newLocation;
   map->setActorAt(newLocation, actor);
}


void ActorManager::addActorToTurnQueue(ActorEntity* actor, int turnTime) {
   turnQueue->insertActor(actor, turnTime);
}


std::pair<int, std::string> ActorManager::calcDamage(ActorEntity* recipient, Damage damage) {
   std::pair<int, std::string> damageAndMessage;

   int constant = damage.constant;
   int diceRoll = Dice::rollDice(damage.dice);

   //TODO: add armor calculations
   damageAndMessage.first = (diceRoll + constant);

   std::string damageMsg = std::to_string(constant+diceRoll);
   damageMsg.append(damageTypeNames[damage.type]);
   damageMsg.append( " damage");

   damageAndMessage.second = damageMsg;

   return damageAndMessage;
}


void ActorManager::damageActor(ActorEntity* actor, int damage) {
   actor->stats.health -= damage;

   if (actor->stats.health <= 0) {
      std::string deathMsg = actor->description.name + " dies.";
      sendMsgIfActorIsVisible(actor, deathMsg);

      destroyActor(actor);
   }
}


void ActorManager::sendMsgIfActorIsVisible(ActorEntity* actor, std::string message) {
   if (map->isVisibleAt(actor->location)) {
      gameLog->sendMessage(message);
   }
}

ActorFactory ActorManager::makeFactory(ItemFactory* itemFactory) {
   return ActorFactory(&actorColiseum, turnQueue, map, itemFactory);
}
