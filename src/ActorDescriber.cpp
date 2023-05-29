#include "Entities/Actors/ActorDescriber.h"
#include "Entities/EntityDescriber.h"


std::string ActorDescriber::describe(ActorEntity* actor) {
   std::string desc = EntityDescriber::makeName(actor->description.name, actor->display);
   desc.append("\n" + actor->description.desc);
   auto effects = actor->activeEffects.getEffects();

   if (effects->empty()) {
      return desc;
   }

   for (int i=0; i<effects->size(); i++) {
      auto item = effects->at(i);
      desc.append("\n"+effectDescriber->getName(item.first.description));
      desc.append(" ("+std::to_string(item.second)+")");
   }

   return desc;
}
