#pragma once

#include "AI.h"
#include "GameObjects/Ability.h"
#include "GameObjects/Item.h"
#include "GraphicsThings/TileDisplay.h"
#include "Enums/TurnTime.h"
#include "Algorithms/PathfindingRoute.h"


struct StatBlock {
	int health, maxHealth;

	/*int strength, dexterity, toughness;
	int wisdom, intelligence, willpower;*/

	int baseMoveSpeed, baseAttackSpeed;

	StatBlock(int health = 0, int maxHealth = 0, /*int strength = 0, int dexterity = 0,
		int toughness = 0, int wisdom = 0, int intelligence = 0, int willpower = 0,*/
		int baseMoveSpeed = FULL_TURN_TIME, int baseAttackSpeed = FULL_TURN_TIME) :
		health(health), maxHealth(maxHealth), /*strength(strength), dexterity(dexterity),
		toughness(toughness), wisdom(wisdom), intelligence(intelligence),
		willpower(willpower),*/ baseMoveSpeed(baseMoveSpeed), baseAttackSpeed(baseAttackSpeed) {};
};

class Actor {
private:
	//location in ActorPool data arena (see Scene/ActorPool/)
	int poolIndex;

	TileDisplay display;
	TileCoords location;

	bool player = false;

	AI ai;
	AIStateID currentState;
	std::vector<TileCoords> visibleTiles;
	std::vector<TileCoords> visibleActorLocations;

	PathingRoute currentRoute;

	//std::vector<Ability> abilities;
	//std::vector<Item>  items;

	//some sort of type/species identifier

	StatBlock stats;

public:
	Actor() : poolIndex(-1), location(TileCoords()), display(TileDisplay()), ai(AI()),
		currentState(AISTATE_IDLE), player(false) {};
	Actor(TileCoords location, TileDisplay display, AI ai, bool player = false) :
		poolIndex(-1), location(location), display(display), ai(ai), player(player),
		currentState(AISTATE_IDLE) {};

	Item generateCorpse();

	void setLocation(TileCoords coordinates);
	void setDisplay(TileDisplay* newDisplay);
	TileCoords getLocation();

	void setPoolIndex(int index);
	int getPoolIndex();
	TileDisplay* getDisplay();
	StatBlock* getStats();

	std::vector<TileCoords>* getVisibleTiles();
	std::vector<TileCoords>* getVisibleActorLocations();
	PathingRoute* getCurrentRoute();

	void clearVisibilityArrays();
	void addVisibleTile(TileCoords tile);
	void addVisibleActorLocation(TileCoords location);

	void makePlayer();
	bool isPlayer();

	void addIdleSubstate(AIState state);
	void addAttackingSubstate(AIState state);

	AIStateID getState();
	void setState(AIStateID stateID);
};
