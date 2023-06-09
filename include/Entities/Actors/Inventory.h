#pragma once

#include "Entities/Items/ItemEntity.h"


class Inventory {
private:
   ItemEntity* meleeWeapon;
   ItemEntity* natMeleeWeapon;

   ItemEntity* magicWeapon;
   ItemEntity* natMagicWeapon;

   ItemEntity* armor;
   ItemEntity* natArmor;

public:
   Inventory(ItemEntity* natMeleeWeapon = nullptr,
   ItemEntity* natMagicWeapon = nullptr, ItemEntity* natArmor = nullptr) :
   natMeleeWeapon(natMeleeWeapon), natMagicWeapon(natMagicWeapon),
   natArmor(natArmor), meleeWeapon(nullptr), magicWeapon(nullptr),
   armor(nullptr) {};

   bool hasMagicWeapon();
   bool hasMeleeWeapon();
   bool hasArmor();
   
   bool hasHeldMeleeWeapon();
   bool hasHeldMagicWeapon();
   bool hasWornArmor();

   ItemEntity* getMeleeWeapon();
   ItemEntity* getMagicWeapon();
   ItemEntity* getArmor();

   void setMeleeWeapon(ItemEntity* weapon);
   void setMagicWeapon(ItemEntity* weapon);
   void setArmor(ItemEntity* armor);

   void setNatMeleeWeapon(ItemEntity* weapon);
   void setNatMagicWeapon(ItemEntity* weapon);
   void setNatArmor(ItemEntity* armor);
};
