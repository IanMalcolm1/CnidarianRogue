#include "Adventure/Scene/TurnQueue.h"


TurnQueue::~TurnQueue() {
	while (frontNode != nullptr) {
      pop();
	}	
}


void TurnQueue::insertNode(TurnQueueNode* node) {
	if (frontNode == nullptr) {
		startTime = 0;
		frontNode = node;
		return;
	}

   if (frontNode->time > node->time) {
      TurnQueueNode* temp = node;
      temp->next = frontNode;
      frontNode = temp;
      return;
   }

	TurnQueueNode* current = frontNode->next;
	TurnQueueNode* previous = frontNode;

	while (current != nullptr && current->time < node->time) {
		previous = current;
		current = current->next;
	}

	previous->next = node;
	previous->next->next = current;

	if (startTime > 1500000000) {
		resetStartTime();
	}
}


void TurnQueue::insert(ActorEntity* actor, int turnTime) {
	int insertedTime = startTime + turnTime;
   insertNode(new TurnQueueNode(actor, insertedTime));
}


void TurnQueue::remove(ActorEntity* actor) {
	if (frontNode == nullptr) {
		return;
	}

	if (frontNode->actor == actor) {
		TurnQueueNode* temp = frontNode;
		frontNode = temp->next;
		delete temp;
		return;
	}

	TurnQueueNode* lastNode = frontNode;
	TurnQueueNode* currentNode = frontNode->next;

	while (currentNode != nullptr) {
		if (frontNode->actor == actor) {
			lastNode->next = currentNode->next;
			delete currentNode;
			return;
		}

		lastNode = currentNode;
		currentNode = currentNode->next;
	}
}



void TurnQueue::insertEffect(Effect effect, ActorEntity* actor, int time) {
	int insertedTime = startTime + time;
   insertNode(new TurnQueueNode(effect, actor, insertedTime));
}

void TurnQueue::removeEffect(Effect effect, ActorEntity* actor) {
	if (frontNode == nullptr) {
		return;
	}

	if (frontNode->actor == actor && frontNode->effect == effect) {
		TurnQueueNode* temp = frontNode;
		frontNode = temp->next;
		delete temp;
		return;
	}

	TurnQueueNode* lastNode = frontNode;
	TurnQueueNode* currentNode = frontNode->next;

	while (currentNode != nullptr) {
		if (currentNode->actor == actor && currentNode->effect == effect) {
			lastNode->next = currentNode->next;
			delete currentNode;
			return;
		}

		lastNode = currentNode;
		currentNode = currentNode->next;
	}
}


TurnQueueNode TurnQueue::pop() {
	if (frontNode == nullptr) {
		return TurnQueueNode(nullptr, 0);
	}

   startTime = frontNode->time;

	TurnQueueNode* formerFrontNode = frontNode;
	frontNode = formerFrontNode->next;
	TurnQueueNode returnNode = (*formerFrontNode);

	delete formerFrontNode;

	return returnNode;
}


void TurnQueue::resetStartTime() {
	int difference = -startTime;
	startTime = 0;
	
	TurnQueueNode* current = frontNode;

	while (current != nullptr) {
		current->time += difference;
      current = current->next;
	}
}
