#include "Entities/Actors/ActorStatBlock.h"
#include <string>



std::string ActorStatBlock::getHealthAsString() {
   std::string healthString;
   float percentHealth = health/(float)maxHealth;

   std::string color = "lightgreen";
   if (percentHealth < 0.33) {
      color = "red";
   }
   else if (percentHealth < 0.66) {
      color = "orange";
   }

   healthString = "Health: </"+color+":";
   healthString.append(std::to_string(health));
   healthString.append("/");
   healthString.append(std::to_string(maxHealth));
   healthString.append("/>");

   return healthString;
}

std::string ActorStatBlock::getStrengthAsString() {
   std::string strengthString = "Strength: ";
   strengthString.append(std::to_string(strength));
   return strengthString;
}

std::string ActorStatBlock::getIntelligenceAsString() {
   std::string intelligenceString = "Intelligence: ";
   intelligenceString.append(std::to_string(intelligence));
   return intelligenceString;
}

std::string ActorStatBlock::getMoveSpeedAsString() {
   std::string moveSpeedString = "Move Speed: ";
   moveSpeedString.append(std::to_string(baseMoveSpeed));
   return moveSpeedString;
}

std::string ActorStatBlock::getAttackSpeedAsString() {
   std::string attackSpeedString = "Attack Speed: ";
   attackSpeedString.append(std::to_string(baseAttackSpeed));
   return attackSpeedString;
}
