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


void TurnQueue::insert(ActorEntity* actor, int turnTime) {
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


void TurnQueue::remove(ActorEntity* actor) {
	if (frontNode == nullptr) {
		return;
	}
	if (frontNode->actor->getId() == actor->getId()) {
		TurnQueueNode* temp = frontNode;
		frontNode = temp->next;
		delete temp;
		return;
	}

	TurnQueueNode* lastNode = frontNode;
	TurnQueueNode* currentNode = frontNode->next;

	while (currentNode != nullptr) {
		if (frontNode->actor->getId() == actor->getId()) {
			lastNode->next = currentNode->next;
			delete currentNode;
			return;
		}

		lastNode = currentNode;
		currentNode = currentNode->next;
	}
}


ActorEntity* TurnQueue::pop() {
	if (frontNode == nullptr) {
		return nullptr;
	}

	TurnQueueNode* formerFrontNode = frontNode;
	frontNode = formerFrontNode->next;

	if (frontNode == nullptr) {
		startTime = 0;
	}

	startTime = formerFrontNode->time;
	ActorEntity* returnActorEntity = formerFrontNode->actor;

	delete formerFrontNode;

	return returnActorEntity;
}


void TurnQueue::resetStartTime() {
	int difference = -startTime;
	startTime = 0;
	
	TurnQueueNode* current = frontNode;

	while (current != nullptr) {
		current->time += difference;
	}
}
