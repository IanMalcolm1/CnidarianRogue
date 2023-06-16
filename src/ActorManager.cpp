#include "Adventure/Scene/ActorManager.h"
#include "Entities/Abilities/Ability.h"
#include "Entities/Actors/AI.h"
#include "Algorithms/FoV.h"
#include "Algorithms/Pathfinding.h"
#include "Entities/Actors/ActorFactory.h"
#include "Adventure/Scene/TurnQueue.h"
#include "Entities/Components.h"
#include "Entities/Damage.h"
#include "Entities/EntityDescriber.h"
#include "EventListener/Listener.h"
#include <cstdlib>
#include <cwchar>
#include <random>


void ActorManager::initialize(TurnQueue *turnQueue, LocalMap *map, GameLog *gameLog, ItemManager* itemMan) {
   this->turnQueue = turnQueue;
   this->map = map;
   this->gameLog = gameLog;
   this->itemMan = itemMan;
}

EntityColiseum<ActorEntity>* ActorManager::getColiseum() { return &actorColiseum; }


void ActorManager::destroyActor(ActorEntity* actor) {
	map->setActorAt(actor->location, nullptr);
	turnQueue->removeActor(actor);

   Inventory* inventory = &actor->inventory;
   if (inventory->hasWornArmor()) {
      itemMan->moveItem(inventory->getArmor(), actor->location);
   }
   if (inventory->hasHeldMeleeWeapon()) {
      itemMan->moveItem(inventory->getMeleeWeapon(), actor->location);
   }
   if (inventory->hasHeldMagicWeapon()) {
      itemMan->moveItem(inventory->getMagicWeapon(), actor->location);
   }

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
   if (actor->ability.type != ABILITY_NONE) {
      actor->ability.currentCooldown = std::max(0, actor->ability.currentCooldown - turnTime);
   }

   turnQueue->insertActor(actor, turnTime);
}


std::pair<int, std::string> ActorManager::calcDamage(ActorEntity* attacker, ActorEntity* recipient, Damage damage, int relevantStat) {
   std::pair<int, std::string> damageAndMessage;
   std::string damageMsg;
   int totalDamage;
   int damVal;

   int damConst = damage.constant + relevantStat;
   int damRoll = randomizer.rollDice(damage.diceSize, damage.dice);
   damVal = damRoll+damConst;

   if (recipient->inventory.hasArmor()) {
      WearableComp* armor = (WearableComp*) recipient->inventory.getArmor()->getComponent(COMPONENT_WEARABLE);
      if (armor->damage.type == damage.type) {
         int defConstant = armor->damage.constant;
         int defRoll = randomizer.rollDice(armor->damage.diceSize, armor->damage.dice);

         int defVal = defConstant+defRoll;
         totalDamage = std::max(0, damVal-defVal);

         damageMsg = std::to_string(damVal);
         damageMsg.append("-"+std::to_string(defVal));
         damageMsg.append("="+std::to_string(totalDamage));
         damageMsg.append(damageTypeNames[damage.type]);
         damageMsg.append( " damage");
      }
      else {
         totalDamage =  damVal;

         damageMsg = std::to_string(totalDamage);
         damageMsg.append(damageTypeNames[damage.type]);
         damageMsg.append( " damage");
      }
   }

   else {
      totalDamage =  damVal;

      damageMsg = std::to_string(totalDamage);
      damageMsg.append(damageTypeNames[damage.type]);
      damageMsg.append( " damage");
   }

   damageAndMessage.first = totalDamage;
   damageAndMessage.second = damageMsg;

   return damageAndMessage;
}


void ActorManager::damageActor(ActorEntity* actor, int damage) {
   actor->stats.health -= damage;

   if (actor->isPlayer()) {
      notifyListeners(EVENT_PLAYERDAMAGED);
   }

   if (actor->stats.health <= 0) {
      std::string deathMsg = EntityDescriber::makeName(actor);
      deathMsg.append(" dies.");

      sendMsgIfActorIsVisible(actor, deathMsg);

      destroyActor(actor);
   }
}

void ActorManager::healActor(ActorEntity* actor, int health) {
   actor->stats.health += health;
   actor->stats.health = std::min(actor->stats.health, actor->stats.maxHealth);

   std::string message = EntityDescriber::makeName(actor);
   message.append(" recieves </" + colorMap.getColor("lightgreen").getString() +":");
   message.append(std::to_string(health) + "\\> points of healing.");

   sendMsgIfActorIsVisible(actor, message);
}


void ActorManager::sendMsgIfActorIsVisible(ActorEntity* actor, std::string message) {
   if (map->isVisibleAt(actor->location)) {
      gameLog->sendMessage(message);
   }
}


void ActorManager::dropItem(ActorEntity* actor, ItemEntity* item) {
   if (item == nullptr) {
      return;
   }

   itemMan->moveItem(item, actor->location);

   std::string actorName = EntityDescriber::makeName(actor);
   std::string itemName = EntityDescriber::makeName(item);
   sendMsgIfActorIsVisible(actor, actorName+" drops "+itemName);
}
