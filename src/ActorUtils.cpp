#include "Entities/Actors/ActorUtils.h"
#include "Entities/EntityDescriber.h"


void ActorUtils::doAttack(ActorEntity* attacker, ActorEntity* defender) {
   DamagingComp* damageComp = (DamagingComp*) attacker->getActiveWeapon()->getComponent(COMPONENT_DAMAGING);
   
   std::string message = EntityDescriber::makeName(attacker);
   message.append(" attacks ");
   message.append(EntityDescriber::makeName(defender));
   message.append(" for ");

   auto damageAndMessage = actorMan->calcDamage(defender, damageComp->damage1);
   message.append(damageAndMessage.second);
   actorMan->sendMsgIfActorIsVisible(defender, message);

   actorMan->damageActor(defender, damageAndMessage.first);
   
   if (attacker->getActiveWeapon()->hasComponent(COMPONENT_EFFECT)) {
      EffectComp* effect = (EffectComp*) attacker->getActiveWeapon()->getComponent(COMPONENT_EFFECT);
      effectMan->attachEffect(effect->effect1, defender);
   }

}
