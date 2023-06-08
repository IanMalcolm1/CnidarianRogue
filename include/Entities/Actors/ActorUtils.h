#pragma once

#include "Adventure/Scene/EffectManager.h"
#include "Adventure/Scene/ItemManager.h"
#include "Algorithms/PathfindingRoute.h"
#include "Entities/Actors/ActorEntity.h"
#include "Entities/Items/ItemEntity.h"
#include "Logs/GameLog.h"


class ActorUtils {
private:
   ActorManager* actorMan;
   ItemManager* itemMan;
   EffectManager* effectMan;
   LocalMap* map;

   PathingRoute lineRoute;

   void sendPickupItemMessage(ActorEntity* actor, ItemEntity* item);
   void dropItem(ActorEntity* actor, ItemEntity* item);

public:
   ActorUtils() : actorMan(nullptr), itemMan(nullptr), effectMan(nullptr) {};

   void initialize(ActorManager* actorManager, ItemManager* itemManager, EffectManager* effectManager, LocalMap* map);
   
   void doAttack(ActorEntity* attacker, ItemEntity* weapon, ActorEntity* defender);
   void doLineAttack(ActorEntity* attacker, ItemEntity* weapon, TileCoords targetTile);
   void attackAlongRoute(ActorEntity* attacker, ItemEntity* weapon, PathingRoute& route);

   void doItemPickup(ItemEntity* item, ActorEntity* actor);
};
