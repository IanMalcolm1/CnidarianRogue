#pragma once

#include <cwchar>
#include <string>
#include "Topography/TileCoordinates.h"
#include "GraphicsThings/TileDisplay.h"


/* Components inheriting from the actual Component class
 * should not contain pointers, whether directly or via
 * a class like std::string or std::vector. Otherwise
 * memory leaks will abound.
 *
 * 'Components' that require pointers should not inherit
 * from the Component struct and should be included
 * directly as part of a subclass of Entity (see
 * ActorEntity or ItemEntity).
 *
 * Neither official nor unofficial components should
 * contain their own logic. That is the domain of the
 * functions that correspond to AiStates.
 */

struct Description {
   std::string name;
   std::string desc;

   Description(std::string name = "noname", std::string desc = "indescribable")
      : name(name), desc(desc) {};
};


enum DamageType {
   DAMAGE_NONE,
   DAMAGE_PHYSICAL,
   DAMAGE_HEAT,
   DAMAGE_COLD
};
struct Damage {
   DamageType type;
   int dice, constant;

   Damage(DamageType type = DAMAGE_NONE, int dice = 0, int constant = 0)
      : type(type), dice(dice), constant(constant) {};
};


enum EffectType {
   EFFECT_NONE,
   EFFECT_POISON,
   EFFECT_REGENERATION,
   EFFECT_STR_INCREASE,
   EFFECT_INT_INCREASE
};
struct Effect {
   EffectType type;

   //can determine both strength of effects and their durations
   int intensity;
   bool permanent;

   Effect(EffectType type = EFFECT_NONE, int intensity = 0, bool permanent = false)
      : type(type), intensity(intensity), permanent(permanent) {};
};

/* Actual Components, lol */
enum ComponentType {
   COMPONENT_DURABILITY = 0,
   COMPONENT_CONSUMABLE = 1,
   COMPONENT_WEARABLE,
   COMPONENT_DAMAGING,

   NUM_COMPONENT_TYPES
};
struct Component {};


struct DurabilityComp : public Component {
   int total, current;

   DurabilityComp(int total, int current) : total(total), current(current) {};
};


struct WearableComp : public Component {
   int dice;
   int constant;

   WearableComp(int dice = 0, int constant = 0) :
      dice(dice), constant(constant) {};
};


struct DamagingComp : public Component {
   Damage damage1, damage2, damage3;

   DamagingComp(Damage damage1 = Damage(), Damage damage2 = Damage(), Damage damage3 = Damage())
      : damage1(damage1), damage2(damage2), damage3(damage3) {};
};


struct ConsumableComp : public Component {
   Effect effect1, effect2, effect3;

   ConsumableComp(Effect effect1 = Effect(), Effect effect2 = Effect(), Effect effect3 = Effect())
      : effect1(effect1), effect2(effect2), effect3(effect3) {};
};
