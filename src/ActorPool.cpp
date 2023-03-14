#include "Scene/ActorPool.h"

Actor* ActorPool::insert(Actor actor) {
	int index;
	if (reusableIndices.size() == 0) {
		index = dirtySlots;
		dirtySlots++;
	}
	else {
		index = reusableIndices.back();
		reusableIndices.pop_back();
	}

	actor.setPoolIndex(index);
	actors[index] = actor;

	return &actors[index];
}


void ActorPool::kill(Actor* actor) {
	int index = actor->getPoolIndex();
	actors[index] = Actor();

	reusableIndices.push_back(index);
}
