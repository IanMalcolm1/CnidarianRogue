#pragma once

#include <vector>
#include "TestActor.h"

struct TurnQueueNode {
	int next;
	int time;

   /* If a node isn't an actor, it is a DoT, or limited time effect
    * and the ActorEntity pointer serves to identify the affected Actor */
   bool isActor;
	ActorEntity* actor;

   Effect effect;
   
   TurnQueueNode() : actor(nullptr), time(0), next(-1), isActor(true), effect() {};
	TurnQueueNode(ActorEntity* actor, int time) : actor(actor), time(time), next(-1), isActor(true), effect() {};
   TurnQueueNode(Effect effect, ActorEntity* actor, int time) : effect(effect), actor(actor), time(time), next(-1), isActor(false) {};
};

class TurnQueue {
private:
   std::vector<TurnQueueNode> nodes;
   std::vector<int> reusableIndices;

   int dirtySlots;
	int frontIndex;

	int startTime;

   int getNextIndex();
   void sortNode(int nodeIndex);
	void resetStartTime();

public:
	TurnQueue() : nodes(1), startTime(0), frontIndex(-1) {};

   bool isEmpty();

	void insertActor(ActorEntity* actor, int turnTime);
	void removeActor(ActorEntity* actor);
   void insertEffect(Effect effect, ActorEntity* actor, int time);
   void removeEffect(Effect effect, ActorEntity* actor);
	TurnQueueNode* pop();
};
