#include "Scene/TurnQueue.h"


TurnQueue::~TurnQueue() {
	while (frontNode != nullptr) {
      pop();
	}	
}


void TurnQueue::insert(ActorEntity* actor, int turnTime) {
	if (frontNode == nullptr) {
		startTime = 0;
		frontNode = new TurnQueueNode(actor, 0);
		return;
	}

	if (startTime > 1500000000) {
		resetStartTime();
	}

	int insertedTime = startTime + turnTime;

   if (frontNode->time > insertedTime) {
      TurnQueueNode* temp = new TurnQueueNode(actor, insertedTime);
      temp->next = frontNode;
      frontNode = temp;
      return;
   }

	TurnQueueNode* current = frontNode->next;
	TurnQueueNode* previous = frontNode;

	while (current != nullptr && current->time < insertedTime) {
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
