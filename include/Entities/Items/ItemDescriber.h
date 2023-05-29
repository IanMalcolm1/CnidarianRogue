#pragma once

#include "Entities/Components.h"
#include "Entities/Damage.h"
#include "Entities/Effects/EffectDescriber.h"
#include "Entities/Items/ItemEntity.h"

class ItemDescriber {
private:
   EffectDescriber* effectDescriber;

   std::string damageNames[DAMAGE_NONE];

   std::string describeDamage(Damage& damage);

public:
   ItemDescriber(EffectDescriber* effectDescriber) :
   effectDescriber(effectDescriber) {
      damageNames[DAMAGE_PHYSICAL] = "phyisical";
      damageNames[DAMAGE_FIRE] = "</red:fire/>";
      damageNames[DAMAGE_FROST] = "</lightblue:frost/>";
      damageNames[DAMAGE_POISON] = "</green:poison/>";
   };
 
   std::string describe(ItemEntity* item);
   std::string describeWeapon(ItemEntity* item);
};
