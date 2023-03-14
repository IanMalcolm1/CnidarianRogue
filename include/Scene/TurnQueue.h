#pragma once

#include <memory>
#include <vector>
#include "GameObjects/Actor.h"

struct TurnQueueNode {
	TurnQueueNode* next;
	Actor* actor;
	int time;

	TurnQueueNode(Actor* actor, int time) : actor(actor), time(time), next(nullptr) {};
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

	void insert(Actor* actor, int turnTime);
	void remove(Actor* actor);
	Actor* pop();
};
