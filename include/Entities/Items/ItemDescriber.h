#pragma once

#include "Entities/Components.h"
#include "Entities/Damage.h"
#include "Entities/Effects/EffectDescriber.h"
#include "Entities/Items/ItemEntity.h"

class ItemDescriber {
private:
   EffectDescriber* effectDescriber;

   std::string getComponentDescriptions(ItemEntity* item);

public:
   ItemDescriber() : effectDescriber(nullptr) {};

   void initialize(EffectDescriber* effectDescriber);
 
   std::string describe(ItemEntity* item);
   std::string describeMinusDesc(ItemEntity* item);
};
