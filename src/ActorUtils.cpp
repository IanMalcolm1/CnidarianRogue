#include "Entities/Actors/ActorUtils.h"


void ActorUtils::doAttack(ActorEntity* attacker, ActorEntity* defender) {
   DamagingComp* damageComp = (DamagingComp*) attacker->getActiveWeapon()->getComponent(COMPONENT_DAMAGING);
   
   std::string message = attacker->description.name;
   message.append(" attacks ");
   message.append(defender->description.name);
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
