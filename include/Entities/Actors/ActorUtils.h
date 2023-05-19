#pragma once

#include "Adventure/Scene/EffectManager.h"
#include "Entities/Actors/ActorEntity.h"
#include "Logs/GameLog.h"


class ActorUtils {
private:
   ActorManager* actorMan;
   EffectManager* effectMan;

public:
   ActorUtils(ActorManager* actorManager, EffectManager* effectMan) :
   actorMan(actorManager), effectMan(effectMan) {};
   
   void doAttack(ActorEntity* attacker, ActorEntity* defender);
};
