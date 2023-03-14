#pragma once

#include <memory>
#include <array>
#include "GameObjects/Actor.h"


#define MAX_ACTORS 1024

//Note the player actor always has ID 0
class ActorPool {
private:
	std::array<Actor, MAX_ACTORS> actors;
	int dirtySlots;

	std::vector<int16_t> reusableIndices;
	
public:
	ActorPool() : dirtySlots(0) {};

	Actor* insert(Actor actor);
	void kill(Actor* actor);
};
