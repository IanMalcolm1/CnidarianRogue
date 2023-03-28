#pragma once

#include <cwchar>
#include <string>


enum DamageType {
   DAMAGE_NONE,
   DAMAGE_PHYSICAL,
   DAMAGE_HEAT,
   DAMAGE_COLD
};
struct Damage {
   DamageType damageType;
   int damageDice;
   int damageConstant;

   Damage() : damageType(DAMAGE_NONE), damageDice(0),
      damageConstant(0) {};
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

   Effect() : type(EFFECT_NONE), intensity(0), permanent(false) {};
};


enum ComponentType {
   COMPONENT_DESCRIBABLE = -1,
   COMPONENT_DURABILITY,
   COMPONENT_CONSUMABLE,
   COMPONENT_WEARABLE,
   COMPONENT_DAMAGING,
   COMPONENT_RENDERABLE
};
struct Component {};


struct DescribableComp : public Component {
   std::string name;
   std::string description;

   DescribableComp() : name(NULL), description(NULL) {};
};


struct DurabilityComp : public Component {
   int currentDurability;
   int totalDurability;
};


struct WearableComp : public Component {
   int armorDice;
   int armorConstant;
};


struct DamagingComp : public Component {
   Damage damage1, damage2, damage3;
};


struct ConsumableComp : public Component {
   Effect effect1, effect2, effect3;
};



/*
struct RenderableComp : public Component {
   TileDisplay display;
};
*/
