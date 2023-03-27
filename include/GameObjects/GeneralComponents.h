#pragma once

#include <string>

struct Description {
	std::string name;
	std::string description;
};


enum DamageType {
   DAMAGE_PHYSICAL
};
struct Damage {
   DamageType type;
   int damage;
};


