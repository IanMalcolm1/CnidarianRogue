#include "Entities/Effects/EffectDescriber.h"
#include "Entities/Effects/Effect.h"


EffectDescriber::EffectDescriber() {
   names[EFFECT_DESC_POISON] = "</green:Poisoned/>";
   messages[EFFECT_DESC_POISON] = " is </green:poisoned/>.";

   names[EFFECT_DESC_STRENGTH] = "</orange:Strengthened/>";
   messages[EFFECT_DESC_STRENGTH] = " grows stronger.";

   names[EFFECT_DESC_INTELLIGENCE] = "</lavender:Enlightened/>";
   messages[EFFECT_DESC_INTELLIGENCE] = "'s mind clears.";
}

std::string EffectDescriber::getName(EffectDescription descID) {
   return names[descID];
}

std::string EffectDescriber::getMessage(EffectDescription descID) {
   return messages[descID];
}
