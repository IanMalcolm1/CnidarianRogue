#include "Adventure/Scene/TurnQueue.h"

int TurnQueue::getNextIndex() {
   int nodeIndex;

   if (isEmpty()) {
      nodeIndex = frontIndex = 0;
      dirtySlots = 1;
      startTime = 0;
   }
   else if (reusableIndices.empty()) {
      nodes.push_back(TurnQueueNode());
      nodeIndex = dirtySlots++;
   }
   else {
      nodeIndex = reusableIndices.back();
      reusableIndices.pop_back();
   }

   return nodeIndex;
}


void TurnQueue::sortNode(int nodeIndex) {
   if (nodeIndex == frontIndex) {
      return;
   }

   if (nodes[frontIndex].time > nodes[nodeIndex].time) {
      nodes[nodeIndex].next = frontIndex;
      frontIndex = nodeIndex;
      return;
   }

   int previous = frontIndex;
   int current = nodes[frontIndex].next;

   while (current != -1 && nodes[current].time <= nodes[nodeIndex].time) {
      previous = current;
      current = nodes[current].next;
   }

   nodes[previous].next = nodeIndex;
   nodes[nodeIndex].next = current;
}


void TurnQueue::insertActor(ActorEntity* actor, int turnTime) {
   int insertedTime = startTime + turnTime;
   int index = getNextIndex();

   actor->activeEffects.updateEffectDurations(turnTime);

   nodes[index] = TurnQueueNode(actor, insertedTime);
   sortNode(index);
}


void TurnQueue::removeActor(ActorEntity* actor) {
   if (isEmpty()) {
      return;
   }

   if (nodes[frontIndex].isActor && nodes[frontIndex].actor == actor) {
      reusableIndices.push_back(frontIndex);
      frontIndex = nodes[frontIndex].next;
      return;
   }

   int previous = frontIndex;
   int current = nodes[frontIndex].next;

   while (current != -1) {
      if (nodes[current].isActor && nodes[current].actor == actor) {
         nodes[previous].next = nodes[current].next;
         reusableIndices.push_back(current);
         return;
      }

      previous = current;
      current = nodes[current].next;
   }
}



void TurnQueue::insertEffect(Effect effect, ActorEntity* actor, int time) {
   int insertedTime = startTime + time;
   int index = getNextIndex();

   nodes[index] = TurnQueueNode(effect, actor, insertedTime);
   sortNode(index);
}

void TurnQueue::removeEffect(Effect effect, ActorEntity* actor) {
   if (isEmpty()) {
      return;
   }

   if (!nodes[frontIndex].isActor && nodes[frontIndex].actor == actor && nodes[frontIndex].effect == effect) {
      reusableIndices.push_back(frontIndex);
      frontIndex = nodes[frontIndex].next;
      return;
   }

   int previous = frontIndex;
   int current = nodes[frontIndex].next;

   while (current != -1) {
      if (!nodes[current].isActor && nodes[current].actor == actor && nodes[current].effect == effect) {
         nodes[previous].next = nodes[current].next;
         reusableIndices.push_back(current);
         return;
      }

      previous = current;
      current = nodes[current].next;
   }
}


TurnQueueNode* TurnQueue::pop() {
   if (isEmpty()) {
      nodes[0] = TurnQueueNode(nullptr, 0);
      return &nodes[0];
   }

   startTime = nodes[frontIndex].time;
   if (startTime > 1000000000) {
      resetStartTime();
   }

   int formerFrontIndex = frontIndex;
   frontIndex = nodes[frontIndex].next;
   reusableIndices.push_back(formerFrontIndex);

   return &nodes[formerFrontIndex];
}


void TurnQueue::resetStartTime() {
   int difference = -startTime;
   startTime = 0;

   for (auto node : nodes) {
      node.time += difference;
   }
}

bool TurnQueue::isEmpty() {
   return frontIndex == -1;
}
