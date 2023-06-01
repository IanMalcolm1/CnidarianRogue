#include "Entities/Effects/Effect.h"
#include "Enums/TurnTime.h"
#include <string>


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


std::string TimedEffectInfo::getDescription() {
   return "for " + std::to_string(duration/FULL_TURN_TIME) + " turn(s)";
}

std::string DoTEffectInfo::getDescription() {
   return "every " + std::to_string(tickTime/FULL_TURN_TIME) + " turn(s) for " + std::to_string(duration/FULL_TURN_TIME) + " turn(s)";
}

std::string EquippedEffectInfo::getDescription() {
   return "while equipped";
}
