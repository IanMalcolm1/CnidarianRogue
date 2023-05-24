#pragma once

#include "Entities/Items/ItemEntity.h"
#include "Entities/EntityColiseum.h"
#include "Topography/LocalMap.h"
#include "GraphicsThings/ColorMap.h"
#include "Topography/TileCoordinates.h"
#include "Entities/Effects/EffectFactory.h"


enum NaturalWeaponType {
   NATWEAP_FIST,
   NATWEAP_POISON_FANGS,
   NUM_NATURALWEAPONS
};


class ItemFactory {
private:
   EntityColiseum<ItemEntity>* coliseum;
   LocalMap* map;

   ColorMap colorMap;

   ItemEntity* naturalWeapons[NUM_NATURALWEAPONS];
   
   EffectFactory effectFactory;

   void registerItem(ItemEntity* item, TileCoords location);

   //Natural weapons
   ItemEntity* makeFists();
   ItemEntity* makePoisonFangs();

public:
   ItemFactory(EntityColiseum<ItemEntity>* coliseum, LocalMap* map) :
   coliseum(coliseum), map(map) {
      for (int i=0; i<NUM_NATURALWEAPONS; i++) {
         naturalWeapons[i] = nullptr;
      }
   };

   //Weapons
   ItemEntity* makeBasicSword(TileCoords location);

   //Consumables
   ItemEntity* makeIntelligenceMushroom(TileCoords location);
   ItemEntity* makeStrengthFruit(TileCoords location);

   ItemEntity* getNaturalWeapon(NaturalWeaponType type);
};
