#pragma once

#include <string>

enum DamageType {
   DAMAGE_PHYSICAL = 0,
   DAMAGE_FIRE,
   DAMAGE_FROST,
   DAMAGE_POISON,
   DAMAGE_NONE //Also number of damage types
};
struct Damage {
   DamageType type;
   int diceSize, dice, constant;

   Damage(DamageType type = DAMAGE_NONE, int diceSize = 6, int dice = 0,
   int constant = 0) : type(type), dice(dice), diceSize(diceSize),
   constant(constant) {};

	bool operator == (const Damage damage) const {
      return (type==damage.type && dice==damage.dice && constant==damage.constant);
   }

   std::string getDescription();
};
