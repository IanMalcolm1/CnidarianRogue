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
   int dice, constant;

   Damage(DamageType type = DAMAGE_NONE, int dice = 0, int constant = 0)
      : type(type), dice(dice), constant(constant) {};

	bool operator == (const Damage damage) const {
      return (type==damage.type && dice==damage.dice && constant==damage.constant);
   }

   std::string getDescription();
};
