#pragma once

#include "GraphicsThings/TileDisplay.h"
#include "GameObjects/GeneralComponents.h"

enum ItemType {
   ITEM_GENERIC,
   ITEM_CONSUMABLE,
   ITEM_MISC,
   ITEM_TOOL,
   ITEM_ARMOR
};

struct Item {
   public:
      ItemType type;
      TileDisplay display;

      Description description;

      Item(ItemType type) : type(type) {};

      TileDisplay* getDisplay();
};
