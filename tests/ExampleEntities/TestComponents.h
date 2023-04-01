#pragma once

#include <cwchar>
#include <string>


struct MyColor {
	uint8_t r;
	uint8_t g;
	uint8_t b;
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
};
struct Effect {
   EffectType type;

   //can determine both strength of effects and their durations
   int intensity;
   bool permanent;

   Effect(EffectType type = EFFECT_NONE, int intensity = 0, bool permanent = false)
      : type(type), intensity(intensity), permanent(permanent) {};
};


enum ComponentType {
   COMPONENT_DURABILITY = 0,
   COMPONENT_CONSUMABLE = 1,
   COMPONENT_WEARABLE,
   COMPONENT_DAMAGING,
   COMPONENT_DISPLAY,
   COMPONENT_DESCRIBABLE,

   NUM_COMPONENT_TYPES
};
struct Component {};


struct TileDisplay : public Component {
	uint8_t symbol;
	MyColor symbolColor;
	MyColor backColor;
};


struct DescribableComp : public Component {
   std::string name;
   std::string desc;

   DescribableComp(std::string name = "noname", std::string desc = "undescribable")
      : name(name), desc(desc) {};
};


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
