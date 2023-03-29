#pragma once

#include <cwchar>
#include <vector>
#include <unordered_map>
#include "TestComponents.h"


enum ItemType {
   ITEM_TOOL,
   ITEM_MISC,
   ITEM_ARMOR,
   ITEM_CONSUMABLE
};


class ItemData {
private:
   TileDisplay display;
   DescribableComp description;

   uint dynamicComponents;
   std::unordered_map<ComponentType, Component*> dynamicComponentPtrs;

public:
   int id;

   ItemData() : /*display(TileDisplay()), */ dynamicComponents(0),
      dynamicComponentPtrs(std::unordered_map<ComponentType, Component*>()) {};

   //TileDisplay* getDisplay();
   DescribableComp* getDescription();

   bool hasComponent(ComponentType type);

   inline Component* getComponent(ComponentType type) {
      if (hasComponent(type)) {
         return dynamicComponentPtrs[type];
      }
      return NULL;
   }
   
};


struct Item {
   int id;
   ItemType type;
   ItemData* data;
};


struct ArmorItemData : public ItemData {
private:
   WearableComp armor;

public:
   Component* getComponent(ComponentType type);
};
