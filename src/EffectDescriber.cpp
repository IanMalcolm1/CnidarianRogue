#include "Entities/Effects/EffectDescriber.h"
#include "Entities/Effects/Effect.h"


EffectDescriber::EffectDescriber() {
   names[EFFECT_DESC_POISON] = "</green:Poison/>";
   adjectives[EFFECT_DESC_POISON] = "</green:Poisoned/>";
   messages[EFFECT_DESC_POISON] = " is </green:poisoned/>.";

   names[EFFECT_DESC_STRENGTH] = "</orange:Strength/>";
   adjectives[EFFECT_DESC_STRENGTH] = "</orange:Strengthened/>";
   messages[EFFECT_DESC_STRENGTH] = " grows stronger.";

   names[EFFECT_DESC_INTELLIGENCE] = "</lavender:Enlightenment/>";
   adjectives[EFFECT_DESC_INTELLIGENCE] = "</lavender:Enlightened/>";
   messages[EFFECT_DESC_INTELLIGENCE] = "'s mind clears.";
}

std::string EffectDescriber::getAdjective(Effect& effect) {
   if (effect.description == EFFECT_DESC_NONE) {
      return "Effect adjective not found";
   }
   return adjectives[effect.description];
}

std::string EffectDescriber::getMessage(Effect& effect) {
   if (effect.description == EFFECT_DESC_NONE) {
      return "Effect message not found";
   }
   return messages[effect.description];
}

std::string EffectDescriber::describe(Effect& effect) {
   if (effect.description == EFFECT_DESC_NONE) {
      return "This effect has no description";
   }
   
   std::string desc = names[effect.description] + "\n";

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

   return desc;
}
