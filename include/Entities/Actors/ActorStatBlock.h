#pragma once

#include "Enums/TurnTime.h"
#include <string>


struct ActorStatBlock {
	int health, maxHealth;

	int strength, intelligence;

	int baseMoveSpeed, baseAttackSpeed;

	ActorStatBlock(int health = 5, int maxHealth = 5, int strength = 0, int intelligence = 0,
   int baseMoveSpeed = FULL_TURN_TIME, int baseAttackSpeed = FULL_TURN_TIME) :
	health(health), maxHealth(maxHealth), strength(strength), intelligence(intelligence),
	baseMoveSpeed(baseMoveSpeed), baseAttackSpeed(baseAttackSpeed) {};

   std::string getHealthAsString();
   std::string getStrengthAsString();
   std::string getIntelligenceAsString();
   std::string getMoveSpeedAsString();
   std::string getAttackSpeedAsString();
};
