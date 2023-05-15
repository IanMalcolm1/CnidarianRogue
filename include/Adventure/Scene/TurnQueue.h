#pragma once

#include <memory>
#include <vector>
#include "Entities/Actors/ActorEntity.h"
#include "Entities/Components.h"
#include "Entities/Effect.h"

struct TurnQueueNode {
	TurnQueueNode* next;
	int time;

   /* If a node isn't an actor, it is a DoT, or limited time effect
    * and the ActorEntity pointer serves to identify the affected Actor */
   bool isActor;
	ActorEntity* actor;
   Effect effect;

	TurnQueueNode(ActorEntity* actor, int time) : actor(actor), time(time), next(nullptr), isActor(true), effect() {};
   TurnQueueNode(Effect effect, ActorEntity* actor, int time) : effect(effect), actor(actor), time(time), isActor(false) {};
};

class TurnQueue {
private:
	int startTime;
	TurnQueueNode* frontNode;

	void resetStartTime();
   void insertNode(TurnQueueNode* node);

public:
	TurnQueue() : startTime(0), frontNode(nullptr) {};
	~TurnQueue();

	void insert(ActorEntity* actor, int turnTime);
	void remove(ActorEntity* actor);
   void insertEffect(Effect effect, ActorEntity* actor, int time);
   void removeEffect(Effect effect, ActorEntity* actor);
	TurnQueueNode pop();
};
