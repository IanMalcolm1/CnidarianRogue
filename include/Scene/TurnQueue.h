#pragma once

#include <memory>
#include <vector>
#include "Entities/ActorEntity.h"

struct TurnQueueNode {
	TurnQueueNode* next;
	ActorEntity* actor;
	int time;

	TurnQueueNode(ActorEntity* actor, int time) : actor(actor), time(time), next(nullptr) {};
};

class TurnQueue {
private:
	int startTime;
	TurnQueueNode* frontNode;

	void resetStartTime();
	void fullDeletion_Recursive(TurnQueueNode* node);

public:
	TurnQueue() : startTime(0), frontNode(nullptr) {};
	~TurnQueue();

	void insert(ActorEntity* actor, int turnTime);
	void remove(ActorEntity* actor);
	ActorEntity* pop();
};
