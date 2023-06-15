#pragma once

#include <string>
#include "Entities/Actors/ActorEntity.h"
#include "Entities/Items/ItemEntity.h"
#include "GraphicsThings/TileDisplay.h"


struct EntityDescriber {
   static std::string makeName(ActorEntity* actor) {
      return EntityDescriber::makeName(actor->description.name, actor->display);
   }

   static std::string makeName(ItemEntity* item) {
      return EntityDescriber::makeName(item->description.name, item->display);
   }
   
   static std::string makeName(std::string name, EntityDisplay disp) {
      name.insert(0, "\\> ");
      name.insert(0, std::string(1, (char)disp.symbol));
      name.insert(0, ":");

      name.insert(0, disp.symbolColor.getString());

      name.insert(0, "</");

      return name;
   }
};
