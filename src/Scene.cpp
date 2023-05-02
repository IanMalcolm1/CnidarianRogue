#include "Adventure/Scene/Scene.h"
#include "Entities/ActorFactory.h"
#include "Enums/PlayerCommands.h"
#include <random>


LocalMap* Scene::getMap() {	return &map; }
ActorFactory* Scene::getActorFactory() { return &actorFactory; }
ItemFactory* Scene::getItemFactory() { return &itemFactory; }

InputConfirmer* Scene::getInputConfirmer() { return &confirmer; }

void Scene::processCommand(PlayerCommand command, Uint16 modification) {
	if (confirmer.isAwaiting()) {
		int confirmationCode = confirmer.getConfirmation();
		if (confirmationCode == CONF_WAITING) {
			return;
		}
		else if (confirmationCode == CONF_CONFIRMED) {
			command = confirmer.getCommand();
		}
	}


	if (playerManager->autoActing) {
		if (command == PC_ESCAPEKEY) {
			playerManager->clearAutoAct();
			return;
		}
		playerManager->doAutoAct();
		return;
	}

	bool needToRunTurn = false;

	//process player move
	if (command < 9) {
		needToRunTurn = playerManager->processDirectionalCommand(command);
	}

	else if (command == PC_WAIT) {
		ActorEntity* player = playerManager->getPlayer();
		actorManager.getTurnQueue()->insert(player, player->stats.baseMoveSpeed);
		needToRunTurn = true;
	}

	else if (command == PC_TOGGLE_LOOK || command == PC_ESCAPEKEY) {
		playerManager->updateInputState(command);
	}


	if (needToRunTurn) {
		actorManager.runActorTurns();
	}
}

void Scene::updateMapDisplay() {
	map.updateMapDisplay();
}

void Scene::runTurnIfAutoMoving() {
	if (!alreadyRanTurn && playerManager->autoActing) {
		playerManager->doAutoAct();
		actorManager.runActorTurns();
	}
	alreadyRanTurn = false;
}


void Scene::startAutoMove() {
	playerManager->startAutoMove(map.getRouteToMouseTile());
}


TurnQueue* Scene::getTurnQueue() {
   return actorManager.getTurnQueue();
}

void Scene::setPlayerAt(TileCoords location) {
   playerManager->placePlayer(location);
}



void Scene::hookupInputManagerListener(Listener* listener) {
   actorManager.addListener(listener);
}
