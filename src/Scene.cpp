#include "Adventure/Scene/Scene.h"
#include "Algorithms/FoV.h"


void Scene::initialize() {
   itemManager.initialize(&map);
   itemManager.initializeFactory(&itemFactory);
   actorManager.initialize(&turnQueue, &map, gameLog);
   actorManager.initializeFactory(&actorFactory, &itemFactory);
   effectManager.initialize(&actorManager, &turnQueue);
   actorUtils.initialize(&actorManager, &itemManager, &effectManager);
   aiRunner.initialize(&map, &actorManager, &actorUtils);

   FoV::calcPlayerFoV(&map, playerManager->getPlayer());
}

LocalMap* Scene::getMap() {	return &map; }
ActorFactory* Scene::getActorFactory() { return &actorFactory; }
ItemFactory* Scene::getItemFactory() { return &itemFactory; }
TurnQueue* Scene::getTurnQueue() { return &turnQueue; }
ItemManager* Scene::getItemManager() { return &itemManager; }
EffectManager* Scene::getEffectManager() { return &effectManager; }
EffectDescriber* Scene::getEffectDescriber() { return effectManager.getEffectDescriber(); }
ActorUtils* Scene::getActorUtils() { return &actorUtils; }


void Scene::runTurn() {
	while (!turnQueue.isEmpty()) {
	TurnQueueNode* node = turnQueue.pop();
      if (node->isActor) {
         if (node->actor->isPlayer()) {
            break;
         }

         aiRunner.runActorTurn(node->actor);
      }

      else {
         effectManager.updateEffect(node->effect, node->actor);
      }
	}

   FoV::calcPlayerFoV(&map, playerManager->getPlayer());
	map.flagNeedToUpdateDisplay();
}

void Scene::startAutoMove() {
   if (playerManager->startAutoMove() == true) {
      runTurn();
   }
}

void Scene::updateMapDisplay() {
	map.updateMapDisplay();
}


void Scene::setPlayerAt(TileCoords location) {
   playerManager->placePlayer(location);
}


void Scene::hookupListeners(Listener* listener, Listener* listener1) {
   actorManager.addListener(listener);
   actorManager.addListener(listener1);
}
