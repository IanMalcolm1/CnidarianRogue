#include "Entities/Actors/ActorDescriber.h"
#include "Entities/EntityDescriber.h"


GameText ActorDescriber::name(ActorEntity* actor) {
   return textMaker->makeGameText(EntityDescriber::makeName(actor->description.name, actor->display));
}

GameText ActorDescriber::describe(ActorEntity* actor) {
   std::string desc = actor->description.desc;
   auto effects = actor->activeEffects.getEffects();

   if (effects->empty()) {
      return textMaker->makeGameText(desc);
   }

   for (int i=0; i<effects->size(); i++) {
      auto item = effects->at(i);
      desc.append("\n"+effectDescriber->getName(item.first.description));
      desc.append(" ("+std::to_string(item.second)+")");
   }

   return textMaker->makeGameText(desc);
}

void ActorDescriber::setGameTextMaker(GameTextMaker* gameTextMaker) {
   textMaker = gameTextMaker;
}
