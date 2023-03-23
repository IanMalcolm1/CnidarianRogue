#include "Scene/Scene.h"
#include <random>


LocalMap* Scene::getMap() {	return &map; }

PlayerManager* Scene::getPlayerManager() {
	return &playerManager;
}

InputConfirmer* Scene::presentConfirmationSignaller() {
	return &confirmer;
}

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

	if (playerManager.autoActing) {
		if (command == PC_ESCAPEKEY) {
			playerManager.clearAutoAct();
			return;
		}
		playerManager.doAutoAct();
		return;
	}

	bool needToRunTurn = false;

	//process player move
	if (command < 9) {
		needToRunTurn = playerManager.processDirectionalCommand(command);

		Actor* player = playerManager.getPlayer();

		if (needToRunTurn) {
			turnQueue.insert(player, player->getStats()->baseMoveSpeed);
		}
	}

	else if (command == PC_WAIT) {
		Actor* player = playerManager.getPlayer();
		turnQueue.insert(player, FULL_TURN_TIME);
		needToRunTurn = true;
	}

	else if (command == PC_TOGGLE_LOOK) {
		playerManager.updateInputState(command);
	}


	if (needToRunTurn) {
		actorManager.runActorTurns();
	}
}

void Scene::updateMapDisplay() {
	map.updateMapDisplay();
}

void Scene::runTurnIfAutoMoving() {
	if (!alreadyRanTurn && playerManager.autoActing) {
		playerManager.doAutoAct();
		actorManager.runActorTurns();
	}
	alreadyRanTurn = false;
}


void Scene::setPlayerAt(TileCoords location) {
	playerManager.placePlayer(location);
}

void Scene::createActorAt(TileCoords location) {
   actorManager.createActorAt(location);
}

void Scene::startAutoMove() {
	playerManager.startAutoMove();
}
