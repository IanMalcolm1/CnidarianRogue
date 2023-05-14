#pragma once

#include <memory>
#include <vector>
#include "Entities/Actors/ActorEntity.h"
#include "Entities/Components.h"

struct TurnQueueNode {
	TurnQueueNode* next;
	int time;

   /* If a node isn't an actor, it is a DoT, or limited time effect
    * and the ActorEntity pointer serves to identify the affected Actor */
   bool isActor;
	ActorEntity* actor;
   Effect effect;

	TurnQueueNode(ActorEntity* actor, int time) : actor(actor), time(time), next(nullptr) {};
};

class TurnQueue {
private:
	int startTime;
	TurnQueueNode* frontNode;

	void resetStartTime();

public:
	TurnQueue() : startTime(0), frontNode(nullptr) {};
	~TurnQueue();

	void insert(ActorEntity* actor, int turnTime);
	void remove(ActorEntity* actor);
	ActorEntity* pop();
};
