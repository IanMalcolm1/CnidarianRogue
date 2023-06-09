#include "Entities/Actors/ActorUtils.h"
#include "Algorithms/Pathfinding.h"
#include "Algorithms/PathingSpecs.h"
#include "Entities/Components.h"
#include "Entities/EntityDescriber.h"
#include "Entities/Items/ItemEntity.h"
#include "Logs/DebugLogger.h"


void ActorUtils::initialize(ActorManager* actorManager, ItemManager* itemManager, EffectManager* effectManager, LocalMap* map) {
   this->actorMan = actorManager;
   this->itemMan = itemManager;
   this->effectMan = effectManager;
   this->map = map;
}



void ActorUtils::doAttack(ActorEntity* attacker, ItemEntity* weapon, ActorEntity* defender) {
   DamagingComp* damageComp = (DamagingComp*) weapon->getComponent(COMPONENT_DAMAGING);
   int relevantStat;
   std::string attackDescriptor;

   if (weapon->hasComponent(COMPONENT_RANGED)) {
      relevantStat = attacker->stats.intelligence;
      attackDescriptor = " blasts ";
   }
   else {
      relevantStat = attacker->stats.strength;
      attackDescriptor = " hits ";
   }
   
   std::string message = EntityDescriber::makeName(attacker);
   message.append(attackDescriptor);
   message.append(EntityDescriber::makeName(defender));
   message.append(" for ");

   auto damageAndMessage = actorMan->calcDamage(attacker, defender, damageComp->damage1, relevantStat);
   message.append(damageAndMessage.second);

   message.append(" using " + EntityDescriber::makeName(weapon));

   actorMan->sendMsgIfActorIsVisible(defender, message);

   actorMan->damageActor(defender, damageAndMessage.first);
   
   if (weapon->hasComponent(COMPONENT_EFFECT)) {
      EffectComp* effect = (EffectComp*) weapon->getComponent(COMPONENT_EFFECT);
      effectMan->attachEffect(effect->effect1, defender);
   }
}

void ActorUtils::doMeleeAttack(ActorEntity* attacker, ActorEntity* defender) {
   ItemEntity* weapon = attacker->inventory.getMeleeWeapon();
   doAttack(attacker, weapon, defender);
}


void ActorUtils::doRangedAttack(ActorEntity* attacker, TileCoords targetTile) {
   if (!map->isInMapBounds(targetTile)) {
      DebugLogger::log("doLineAttack() target tile out of bounds");
      return;
   }

   ItemEntity* weapon = attacker->inventory.getMagicWeapon();

   PathingSpecs specs = PathingSpecs(PATH_LINE, TRAV_IGNORE_NONE);
   specs.lineInfo.range = ((RangedComp*)weapon->getComponent(COMPONENT_RANGED))->range;
   specs.start = attacker->location;
   specs.end = targetTile;

   Pathfinding::calcPath(specs, map, lineRoute);

   attackAlongRoute(attacker, weapon, lineRoute);
}


void ActorUtils::attackAlongRoute(ActorEntity* attacker, ItemEntity* weapon, PathingRoute& route) {


   route.resetProgress();
   while (route.hasNextTile()) {
      TileCoords coords = route.getNextTile();
      if (map->thereIsAnActorAt(coords)) {
         doAttack(attacker, weapon, map->getActorAt(coords));
      }
      route.incrementProgress();
   }
}


void ActorUtils::doItemPickup(ItemEntity *item, ActorEntity* actor) {
   TileCoords currLocation = item->location;
   Inventory* inventory = &actor->inventory;
   itemMan->moveItem(item, {-1,-1});

   if (item->hasComponent(COMPONENT_WIELDABLE)) {
      if (item->hasComponent(COMPONENT_RANGED)) {
         if (inventory->hasHeldMagicWeapon()) {
            actorMan->dropItem(actor, inventory->getMagicWeapon());
         }
         inventory->setMagicWeapon(item);
         sendPickupItemMessage(actor, item);
      }
      else {
         if (inventory->hasHeldMeleeWeapon()) {
            actorMan->dropItem(actor, inventory->getMeleeWeapon());
         }
         inventory->setMeleeWeapon(item);
         sendPickupItemMessage(actor, item);
      }
   }

   else if (item->hasComponent(COMPONENT_WEARABLE)) {
      if (inventory->hasWornArmor()) {
         itemMan->moveItem(inventory->getArmor(), currLocation);
         actorMan->dropItem(actor, inventory->getArmor());
      }
      inventory->setArmor(item);
      sendPickupItemMessage(actor, item);
   }

   else if (item->hasComponent(COMPONENT_CONSUMABLE)) {
      sendPickupItemMessage(actor, item);

      EffectComp* effectComp = (EffectComp*) item->getComponent(COMPONENT_EFFECT);
      effectMan->attachEffect(effectComp->effect1, actor);

      ConsumableComp* consumableComp = (ConsumableComp*) item->getComponent(COMPONENT_CONSUMABLE);
      consumableComp->charges--;
      if (consumableComp->charges <= 0) {
         itemMan->destroyItem(item);
      }
   }

   else {
      itemMan->moveItem(item, currLocation);
      if (actor->isPlayer()) {
         actorMan->sendMsgIfActorIsVisible(actor, "This item cannot be picked up.");
      }
   }

}


void ActorUtils::sendPickupItemMessage(ActorEntity* actor, ItemEntity* item) {
   std::string actorName = EntityDescriber::makeName(actor);
   std::string itemName = EntityDescriber::makeName(item);
   actorMan->sendMsgIfActorIsVisible(actor, actorName+" picks up "+itemName);
}

