#include "Entities/Actors/ActorDescriber.h"
#include "Entities/EntityDescriber.h"


std::string ActorDescriber::describe(ActorEntity* actor) {
   std::string desc = EntityDescriber::makeName(actor);
   desc.append("\n" + actor->description.desc);


   if (!actor->activeEffects.getAllEffects()->empty()) {
      desc.append("\n"+listEffects(actor));
   }

   return desc;
}


std::string ActorDescriber::listEffects(ActorEntity *actor) {
   auto effects = actor->activeEffects.getAllEffects();

   if (effects->empty()) {
      return "";
   }

   std::string listing = "Active Effects:";

   for (int i=0; i<effects->size(); i++) {
      auto effect = effects->at(i);
      listing.append("\n"+effectDescriber->getAdjective(effect));
      listing.append("\n"+effectDescriber->describe(effect));
   }

   return listing;
}
