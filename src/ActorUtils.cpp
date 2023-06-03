#include "Entities/Actors/ActorUtils.h"
#include "Entities/Components.h"
#include "Entities/EntityDescriber.h"


void ActorUtils::initialize(ActorManager* actorManager, ItemManager* itemManager, EffectManager* effectManager) {
   this->actorMan = actorManager;
   this->itemMan = itemManager;
   this->effectMan = effectManager;
}



void ActorUtils::doAttack(ActorEntity* attacker, ActorEntity* defender) {
   DamagingComp* damageComp = (DamagingComp*) attacker->getActiveWeapon()->getComponent(COMPONENT_DAMAGING);
   
   std::string message = EntityDescriber::makeName(attacker);
   message.append(" attacks ");
   message.append(EntityDescriber::makeName(defender));
   message.append(" for ");

   auto damageAndMessage = actorMan->calcDamage(attacker, defender, damageComp->damage1);
   message.append(damageAndMessage.second);
   actorMan->sendMsgIfActorIsVisible(defender, message);

   actorMan->damageActor(defender, damageAndMessage.first);
   
   if (attacker->getActiveWeapon()->hasComponent(COMPONENT_EFFECT)) {
      EffectComp* effect = (EffectComp*) attacker->getActiveWeapon()->getComponent(COMPONENT_EFFECT);
      effectMan->attachEffect(effect->effect1, defender);
   }
}

void ActorUtils::doItemPickup(ItemEntity *item, ActorEntity* actor) {
   TileCoords currLocation = item->location;
   itemMan->moveItem(item, {-1,-1});

   if (item->hasComponent(COMPONENT_WIELDABLE)) {
      if (actor->getHeldWeapon() != nullptr) {
         itemMan->moveItem(actor->getHeldWeapon(), currLocation);
      }
      actor->setWeapon(item);
   }

   else if (item->hasComponent(COMPONENT_CONSUMABLE)) {
      EffectComp* effectComp = (EffectComp*) item->getComponent(COMPONENT_EFFECT);
      effectMan->attachEffect(effectComp->effect1, actor);

      ConsumableComp* consumableComp = (ConsumableComp*) item->getComponent(COMPONENT_CONSUMABLE);
      consumableComp->charges--;
      if (consumableComp->charges <= 0) {
         itemMan->destroyItem(item);
      }
   }
}
