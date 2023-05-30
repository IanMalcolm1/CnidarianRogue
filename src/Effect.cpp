#include "Entities/Effects/Effect.h"


std::string StatModEffectInfo::getDescription() {
   std::string desc = "Adds " + std::to_string(modification) + " to ";

   switch(stat) {
   case STAT_MAX_HEALTH:
      desc.append("max health");
      break;
   case STAT_STRENGTH:
      desc.append("strength");
      break;
   case STAT_INTELLIGENCE:
      desc.append("intelligence");
      break;
   case STAT_SPEED:
      desc.append("speed");
      break;
   default:
      desc.append("invalid stat type");
      break;
   }

   return desc;
}
