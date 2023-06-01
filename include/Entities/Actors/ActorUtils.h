#pragma once

#include "Adventure/Scene/EffectManager.h"
#include "Adventure/Scene/ItemManager.h"
#include "Entities/Actors/ActorEntity.h"
#include "Entities/Items/ItemEntity.h"
#include "Logs/GameLog.h"


class ActorUtils {
private:
   ActorManager* actorMan;
   ItemManager* itemMan;
   EffectManager* effectMan;

public:
   ActorUtils(ActorManager* actorManager, ItemManager* itemManager,
   EffectManager* effectManager) : actorMan(actorManager),
   itemMan(itemManager), effectMan(effectManager) {};
   
   void doAttack(ActorEntity* attacker, ActorEntity* defender);
   void doItemPickup(ItemEntity* item, ActorEntity* actor);
};
