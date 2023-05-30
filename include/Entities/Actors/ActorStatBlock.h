#pragma once

#include "Enums/TurnTime.h"
#include <string>


struct ActorStatBlock {
	int health, maxHealth;
	int strength, intelligence;
	int speed, baseSpeed;

	ActorStatBlock(int health = 5, int maxHealth = 5, int strength = 0,
   int intelligence = 0, int speed = FULL_TURN_TIME) :
	health(health), maxHealth(maxHealth), strength(strength),
   intelligence(intelligence), speed(speed) {};

   std::string getHealthAsString();
   std::string getStrengthAsString();
   std::string getIntelligenceAsString();
   std::string getSpeedAsString();
};


enum StatType {
   STAT_HEALTH,
   STAT_MAX_HEALTH,
   STAT_STRENGTH,
   STAT_INTELLIGENCE,
   STAT_SPEED
};
