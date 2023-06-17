#pragma once

#include "Entities/Items/ItemEntity.h"
#include "Entities/EntityColiseum.h"
#include "Topography/LocalMap.h"
#include "GraphicsThings/ColorLibrary.h"
#include "Topography/TileCoordinates.h"


enum NaturalWeaponType {
   NATWEAP_FIST,
   NATWEAP_POISON_SKIN,
   NATWEAP_CNIDAS_BUDS,
   NATWEAP_FANGS,
   NATWEAP_FORCE_CANTRIP,
   NATWEAP_TOUGH_SKIN, //yes, this is armor
   NUM_NATURALWEAPONS
};


class ItemFactory {
private:
   EntityColiseum<ItemEntity>* coliseum;
   LocalMap* map;

   ColorLibrary colorMap;

   ItemEntity* naturalWeapons[NUM_NATURALWEAPONS];
   
   void registerItem(ItemEntity* item, TileCoords location);

   //Natural weapons
   ItemEntity* makeFists();
   ItemEntity* makePoisonSkin();
   ItemEntity* makeFangs();
   ItemEntity* makeForceCantrip();
   ItemEntity* makeToughSkin();
   ItemEntity* makeCnidasBuds();

public:
   ItemFactory() : coliseum(nullptr), map(nullptr) {
      for (int i=0; i<NUM_NATURALWEAPONS; i++) {
         naturalWeapons[i] = nullptr;
      }
   };

   void initialize(EntityColiseum<ItemEntity>* coliseum, LocalMap* map);

   //Weapons
   ItemEntity* makeBasicDagger(TileCoords location);
   ItemEntity* makeBasicSword(TileCoords location);
   ItemEntity* makeBasicMace(TileCoords location);
   ItemEntity* makeBigMace(TileCoords location);
   ItemEntity* makeForceWand(TileCoords location);

   //Armor
   ItemEntity* makeGambeson(TileCoords location);
   ItemEntity* makeLeatherArmor(TileCoords location);

   //Consumables
   ItemEntity* makeIntelligenceMushroom(TileCoords location);
   ItemEntity* makeStrengthFruit(TileCoords location);

   ItemEntity* getNaturalWeapon(NaturalWeaponType type);
};
