#include "Entities/Effects/EffectDescriber.h"
#include "Entities/Effects/Effect.h"


EffectDescriber::EffectDescriber() {
   names[EFFECT_POISON] = "</green:Poison\\>";
   adjectives[EFFECT_POISON] = "</green:Poisoned\\>";
   messages[EFFECT_POISON] = " is </green:poisoned\\>.";

   names[EFFECT_STRENGTH] = "</orange:Strength\\>";
   adjectives[EFFECT_STRENGTH] = "</orange:Strengthened\\>";
   messages[EFFECT_STRENGTH] = " grows stronger.";

   names[EFFECT_INTELLIGENCE] = "</lavender:Enlightenment\\>";
   adjectives[EFFECT_INTELLIGENCE] = "</lavender:Enlightened\\>";
   messages[EFFECT_INTELLIGENCE] = "'s mind clears.";

   names[EFFECT_HEAL] = "</lightgreen:Regeneration\\>";
   adjectives[EFFECT_HEAL] = "</lightgreen:Regenerating\\>";
   messages[EFFECT_HEAL] = "'s wounds close.";
}

std::string EffectDescriber::getAdjective(Effect& effect) {
   if (effect.name == EFFECT_NONAME) {
      return "Effect adjective not found";
   }
   return adjectives[effect.name];
}

std::string EffectDescriber::getMessage(Effect& effect) {
   if (effect.name == EFFECT_NONAME) {
      return "Effect message not found";
   }
   return messages[effect.name];
}

std::string EffectDescriber::nameAndDescribe(Effect &effect) {
   if (effect.name == EFFECT_NONAME) {
      return "This effect has no name";
   }
   
   std::string desc = names[effect.name] + "\n";
   desc.append(describe(effect));

   return desc;
}

std::string EffectDescriber::describe(Effect& effect) {
   if (effect.name == EFFECT_NONAME) {
      return "This effect has no name";
   }

   std::string desc = "";

   switch(effect.type) {
   case EFFECT_TYPE_NONE:
      desc.append("Bad effect type");
      break;
   case EFFECT_TYPE_DAMAGE:
      desc.append(effect.damageInfo.damage.getDescription());
      break;
   case EFFECT_TYPE_STAT_MOD:
      desc.append(effect.statModInfo.getDescription());
      break;
   }

   switch (effect.timing) {
   case EFFECT_TIMING_PERMANENT:
      desc.append(" (permanent)");
      break;
   case EFFECT_TIMING_DOT:
      desc.append(" "+effect.dotInfo.getDescription());
      break;
   case EFFECT_TIMING_EQUIPPED:
      desc.append(" "+effect.equippedInfo.getDescription());
      break;
   case EFFECT_TIMING_TIMED:
      desc.append(" "+effect.timedInfo.getDescription());
      break;
   }

   return desc;
}
