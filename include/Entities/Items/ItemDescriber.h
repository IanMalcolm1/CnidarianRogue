#pragma once

#include "Entities/Components.h"
#include "Entities/Damage.h"
#include "Entities/Effects/EffectDescriber.h"
#include "Entities/Items/ItemEntity.h"
#include "GraphicsThings/GameText.h"

class ItemDescriber {
private:
   GameTextMaker* textMaker;
   EffectDescriber* effectDescriber;

   std::string damageNames[DAMAGE_NONE];

   std::string describeDamage(DamagingComp* damage);

public:
   ItemDescriber(GameTextMaker* gameTextMaker, EffectDescriber* effectDescriber) :
   textMaker(gameTextMaker), effectDescriber(effectDescriber) {
      damageNames[DAMAGE_PHYSICAL] = "phyisical";
      damageNames[DAMAGE_FIRE] = "</red:fire/>";
      damageNames[DAMAGE_FROST] = "</lightblue:frost/>";
      damageNames[DAMAGE_POISON] = "</green:poison/>";
   };

   void setGameTextMaker(GameTextMaker* gameTextMaker);

   GameText name(ItemEntity* item);
   GameText describe(ItemEntity* item);
   GameText describeInDepth(ItemEntity* item);
};
