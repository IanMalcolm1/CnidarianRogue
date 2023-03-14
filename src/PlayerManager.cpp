#include "PlayerManager/PlayerManager.h"

void PlayerManager::initialize(LocalMap* map, InputConfirmer* sceneConfirmer, TurnQueue* queue) {
	this->map = map;
	this->sceneConfirmer = sceneConfirmer;

	TileDisplay playerDisp = { ASYM_AT, {255,255,255}, {0,0,0} };
	player.setDisplay(&playerDisp);
	player.makePlayer();

	queue->insert(&player, 0);
}

bool PlayerManager::processDirectionalCommand(PlayerCommand direction) {
	TileCoords oldCoords, newCoords;

	if (inputState == PLAYER_INPUT_MOVE) {
		oldCoords = newCoords = player.getLocation();
	}
	else {
		oldCoords = newCoords = map->getFocusTileLocation();
	}

	if (direction < 3) {
		newCoords.y--;
	}
	else if (direction < 6) {
		newCoords.y++;
	}
	if (direction % 3 == 1) {
		newCoords.x++;
	}
	else if (direction % 3 == 2) {
		newCoords.x--;
	}

	if (!map->isInMapBounds(newCoords)) {
		return false;
	}

	if (inputState == PLAYER_INPUT_MOVE) {
		if (map->isTraversibleAt(newCoords) && !map->thereIsAnActorAt(newCoords)) {
			map->setPlayerLocation(&player, newCoords);
			return true;
		}
	}
	else if (inputState == PLAYER_INPUT_MOVE) {
		map->setLookTile(oldCoords, newCoords);
		return false;
	}
}

Actor* PlayerManager::getPlayer() {
	return &player;
}

void PlayerManager::placePlayer(TileCoords location) {
	map->setPlayerLocation(&player, location);
}

void PlayerManager::updateInputState(PlayerCommand command) {
	if (command == PC_TOGGLE_LOOK) {
		if (inputState == PLAYER_INPUT_LOOK) {
			map->stopLooking();
			inputState = PLAYER_INPUT_MOVE;
		}
		else {
			map->setLookTile(player.getLocation());
			inputState = PLAYER_INPUT_LOOK;
		}
	}

	else if (command == PC_ESCAPEKEY) {
		map->stopLooking();
		inputState = PLAYER_INPUT_MOVE;
	}
}

int PlayerManager::doAutoAct() {
	if (!autoMoveRoute.hasNextTile()) {
		autoActing = false;
		autoMoveRoute.clear();
		return 0;
	}

	TileCoords newTile = autoMoveRoute.getNextTile();

	if (map->isTraversibleAt(newTile)) {
		map->setPlayerLocation(&player, newTile);
		autoMoveRoute.incrementProgress();
	}
	else {
		autoActing = false;
		autoMoveRoute.clear();
	}

	return FULL_TURN_TIME;
}

void PlayerManager::clearAutoAct() {
	autoMoveRoute.clear();
	autoActing = false;
}

void PlayerManager::startAutoMove() {
	autoMoveRoute = map->getRouteToMouseTile();
	autoMoveRoute.resetProgress();
	autoActing = true;
}
