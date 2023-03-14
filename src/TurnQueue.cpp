#include "Scene/TurnQueue.h"


TurnQueue::~TurnQueue() {
	if (frontNode != nullptr) {
		fullDeletion_Recursive(frontNode);
	}	
}


void TurnQueue::fullDeletion_Recursive(TurnQueueNode* node) {
	if (node->next != nullptr) {
		fullDeletion_Recursive(node->next);
		delete node;
	}
}


void TurnQueue::insert(Actor* actor, int turnTime) {
	if (frontNode == nullptr) {
		startTime = 0;
		frontNode = new TurnQueueNode(actor, 0);
		return;
	}

	if (startTime > 2000000000) {
		resetStartTime();
	}

	TurnQueueNode* current = frontNode->next;
	TurnQueueNode* previous = frontNode;

	int insertedTime = startTime + turnTime;

	while (current != nullptr && current->time <= insertedTime) {
		previous = current;
		current = current->next;
	}

	previous->next = new TurnQueueNode(actor, insertedTime);
	previous->next->next = current;
}


void TurnQueue::remove(Actor* actor) {
	if (frontNode == nullptr) {
		return;
	}
	if (frontNode->actor->getPoolIndex() == actor->getPoolIndex()) {
		TurnQueueNode* temp = frontNode;
		frontNode = temp->next;
		delete temp;
		return;
	}

	TurnQueueNode* lastNode = frontNode;
	TurnQueueNode* currentNode = frontNode->next;

	while (currentNode != nullptr) {
		if (frontNode->actor->getPoolIndex() == actor->getPoolIndex()) {
			lastNode->next = currentNode->next;
			delete currentNode;
			return;
		}

		lastNode = currentNode;
		currentNode = currentNode->next;
	}
}


Actor* TurnQueue::pop() {
	if (frontNode == nullptr) {
		return nullptr;
	}

	TurnQueueNode* formerFrontNode = frontNode;
	frontNode = formerFrontNode->next;

	if (frontNode == nullptr) {
		startTime = 0;
	}

	startTime = formerFrontNode->time;
	Actor* returnActor = formerFrontNode->actor;

	delete formerFrontNode;

	return returnActor;
}


void TurnQueue::resetStartTime() {
	int difference = -startTime;
	startTime = 0;
	
	TurnQueueNode* current = frontNode;

	while (current != nullptr) {
		current->time += difference;
	}
}
