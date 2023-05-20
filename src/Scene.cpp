#include "Adventure/Scene/Scene.h"
#include "Entities/Actors/ActorFactory.h"
#include "Enums/PlayerCommands.h"
#include <random>


LocalMap* Scene::getMap() {	return &map; }
ActorFactory* Scene::getActorFactory() { return &actorFactory; }
ItemFactory* Scene::getItemFactory() { return &itemFactory; }
TurnQueue* Scene::getTurnQueue() { return &turnQueue; }
ItemManager* Scene::getItemManager() { return &itemManager; }
EffectManager* Scene::getEffectManager() { return &effectManager; }


void Scene::runTurn() {
	TurnQueueNode node = turnQueue.pop();
	while (node.actor != nullptr) {
      if (node.isActor) {
         if (node.actor->isPlayer()) {
            break;
         }

         aiRunner.runActorTurn(node.actor);
      }

      else {
         effectManager.applyEffect(node.effect, node.actor);
      }

		node = turnQueue.pop();
	}

	map.flagNeedToUpdateDisplay();
}

void Scene::updateMapDisplay() {
	map.updateMapDisplay();
}


void Scene::setPlayerAt(TileCoords location) {
   playerManager->placePlayer(location);
}


void Scene::hookupInputManagerListener(Listener* listener) {
   actorManager.addListener(listener);
}
