#include "Adventure/Scene/TurnRunner.h"



void TurnRunner::runTurn() {
	TurnQueueNode node = turnQueue.pop();
	while (node.actor != nullptr) {
      if (node.isActor) {
         if (node.actor->isPlayer) {
            break;
         }

		   int timeTaken = runAction(node.actor);
		   turnQueue.insert(node.actor, timeTaken);
      }

      else {
         effectMan.applyEffect(node.effect, node.actor);
      }

		node = turnQueue.pop();
	}

	map->flagNeedToUpdateDisplay();
}
