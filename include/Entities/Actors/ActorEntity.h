#pragma once

#include "Entities/Actors/AI.h"
#include "Entities/Components.h"
#include "Entities/Effects/EffectList.h"
#include "Entities/Items/ItemEntity.h"
#include "GraphicsThings/TileDisplay.h"
#include "Enums/TurnTime.h"
#include "Algorithms/PathfindingRoute.h"
#include "Entities/Actors/ActorStatBlock.h"
#include <cwchar>

enum Faction {
   FACTION_GOOD,
   FACTION_BAD,
   FACTION_PACIFIST
};

class ActorEntity : public Entity {
private:
	bool player;

	AI ai;

	std::vector<TileCoords> visibleTiles;
	std::vector<ActorEntity*> visibleActors;
	PathingRoute currentRoute;
   ActorEntity* targetEntity;

   ItemEntity* magicWeapon;
   ItemEntity* physicalWeapon;
   ItemEntity* natMagicWeapon;
   ItemEntity* natPhyisicalWeapon;

   ItemEntity* armor;

public:
   EffectList activeEffects;
	ActorStatBlock stats;
	EntityDisplay display;
	TileCoords location;
   Description description;
   Faction faction;


	ActorEntity(int id, int bytesUsed, int totalSpace, bool player = false)
   : Entity(id, bytesUsed, totalSpace), location(TileCoords()),
   display(EntityDisplay()), ai(AI()), player(player), targetEntity(nullptr),
   physicalWeapon(nullptr), magicWeapon(nullptr),
   natPhyisicalWeapon(nullptr), natMagicWeapon(nullptr) {};

   void reset();

   bool isPlayer();

	std::vector<TileCoords>* getVisibleTiles();
	std::vector<ActorEntity*>* getVisibleActors();
	PathingRoute* getCurrentRoute();

   void setFaction(Faction newFaction);
   bool isHostileTo(ActorEntity* actor);
   void checkForHostiles();
   bool canSeeHostile();
   bool isTargetting(ActorEntity* actor);
   void setTarget(ActorEntity* actor);
   ActorEntity* getTarget();
   bool canSeeTarget();
   void chooseTarget();

	void clearVisibilityArrays();
	void addVisibleTile(TileCoords tile);
	void addVisibleActor(ActorEntity* actor);

	void addIdleSubstate(AiState state);
	void addAttackingSubstate(AiState state);
   bool isAggroed();
	AiStateId getState();
	void setState(AiStateId stateID);

   ItemEntity* getPhysicalWeapon();
   ItemEntity* getMagicWeapon();
   ItemEntity* getPhysicalWeaponDirect();
   ItemEntity* getMagicWeaponDirect();
   bool hasDedicatedPhysicalWeapon();
   bool hasDedicatedMagicWeapon();
   void setNaturalPhysicalWeapon(ItemEntity* weapon);
   void setNaturalMagicWeapon(ItemEntity* weapon);
   void setPhysicalWeapon(ItemEntity* weapon);
   void setMagicWeapon(ItemEntity* weapon);

   bool hasArmor();
   ItemEntity* getArmor();
   void setArmor(ItemEntity* armor);
};
