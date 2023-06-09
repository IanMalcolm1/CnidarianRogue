#include "Entities/Actors/Inventory.h"


bool Inventory::hasMagicWeapon() {
   return getMagicWeapon() != nullptr;
}
bool Inventory::hasMeleeWeapon() {
   return getMeleeWeapon() != nullptr;
}
bool Inventory::hasArmor() {
   return getArmor() != nullptr;
}


bool Inventory::hasHeldMeleeWeapon() {
   return meleeWeapon != nullptr;
}
bool Inventory::hasHeldMagicWeapon() {
   return magicWeapon != nullptr;
}
bool Inventory::hasWornArmor() {
   return armor != nullptr;
}


ItemEntity* Inventory::getMeleeWeapon() {
   if (meleeWeapon == nullptr) {
      return natMeleeWeapon;
   }
   return meleeWeapon;
}
ItemEntity* Inventory::getMagicWeapon() {
   if (magicWeapon == nullptr) {
      return natMagicWeapon;
   }
   return magicWeapon;
}
ItemEntity* Inventory::getArmor() {
   if (armor == nullptr) {
      return natArmor;
   }
   return armor;
}

void Inventory::setMeleeWeapon(ItemEntity* weapon) {
   meleeWeapon = weapon;
}
void Inventory::setMagicWeapon(ItemEntity* weapon) {
   magicWeapon = weapon;
}
void Inventory::setArmor(ItemEntity* armor) {
   this->armor = armor;
}


void Inventory::setNatMeleeWeapon(ItemEntity* weapon) {
   natMeleeWeapon = weapon;
}
void Inventory::setNatMagicWeapon(ItemEntity* weapon) {
   natMagicWeapon = weapon;
}
void Inventory::setNatArmor(ItemEntity* armor) {
   natArmor = armor;
}
