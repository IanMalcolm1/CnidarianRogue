#include "Adventure/Scene/Scene.h"
#include "Entities/ActorFactory.h"
#include "Enums/PlayerCommands.h"
#include <random>


LocalMap* Scene::getMap() {	return &map; }
ActorFactory* Scene::getActorFactory() { return &actorFactory; }
ItemFactory* Scene::getItemFactory() { return &itemFactory; }
TurnQueue* Scene::getTurnQueue() { return actorManager.getTurnQueue(); };


void Scene::runTurn() {
   actorManager.runActorTurns();
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
