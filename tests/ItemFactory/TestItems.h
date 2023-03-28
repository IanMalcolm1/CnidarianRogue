#pragma once

#include <cwchar>
#include <vector>
#include "TestComponents.h"


enum ItemType {
   ITEM_TOOL,
   ITEM_MISC,
   ITEM_ARMOR,
   ITEM_CONSUMABLE
};


class ItemData {
private:
   //TileDisplay display;
   DescribableComp description;

   uint hardcodedComponents;
   uint dynamicComponents;
   std::vector<Component*> dynamicComponentPtrs;

public:
   int id;
};


struct Item {
   int id;
   ItemType type;
   ItemData* data;
};


struct ArmorItemData : public ItemData {
   WearableComp armor;
};
