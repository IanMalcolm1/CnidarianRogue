#include "Entities/Effects/EffectList.h"


std::pair<Effect,int>* EffectList::getEffect(Effect effect) {
   for (int i=0; i<list.size(); i++) {
      if (list[i].first == effect) {
         return &list[i];
      }
   }
   return nullptr;
}

void EffectList::addEffect(Effect effect) {
   list.push_back({effect,1});
}

void EffectList::removeEffect(Effect effect) {
   for (int i=0; i<list.size(); i++) {
      if (list[i].first==effect) {
         list.erase(list.begin()+i);
      }
   }
}


std::vector<std::pair<Effect,int>>*  EffectList::getEffects() {
   return &list;
}
