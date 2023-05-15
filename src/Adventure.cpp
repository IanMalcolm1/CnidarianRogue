#include "Adventure/Adventure.h"
#include "Enums/PlayerCommands.h"

void Adventure::linkPlayerAndScene() {
   playerMan.setSceneDependencies(scene.getTurnQueue(), scene.getMap(), scene.getEffectManager(), scene.getItemManager(), scene.getItemFactory());
}


Scene* Adventure::getScene() {
   return &scene;
}

void Adventure::changeScene() {
   scene.~Scene();
   scene = Scene(&log, &playerMan);
   linkPlayerAndScene();
}


GameLog* Adventure::getGameLog() {
   return &log;
}
PlayerManager* Adventure::getPlayerManager() {
   return &playerMan;
}


void Adventure::processCommand(PlayerCommand command, Uint16 modification) {
	if (playerMan.autoActing) {
		if (command == PC_ESCAPEKEY) {
			playerMan.clearAutoAct();
			return;
		}
		playerMan.doAutoAct();
		return;
	}

	bool needToRunTurn = false;

	//process player move
   if (command < 9) {
      needToRunTurn = playerMan.processDirectionalCommand(command);
   }

   else if (command == PC_PICKUP) {
      needToRunTurn = playerMan.pickUpItem();
   }

   else if (command == PC_WAIT) {
      playerMan.waitTurn();
      needToRunTurn = true;
   }

   else if (command == PC_TOGGLE_LOOK || command == PC_ESCAPEKEY) {
      playerMan.updateInputState(command);
   }


   if (needToRunTurn) {
      scene.runTurn();
   }
}

void Adventure::processClick(bool ctrlDown) {

}

void Adventure::runTurnIfAutoMoving() {
	if (!alreadyRanTurn && playerMan.autoActing) {
		playerMan.doAutoAct();
      scene.runTurn();
	}
	alreadyRanTurn = false;
}
void Adventure::updateMapDisplay() {
   scene.updateMapDisplay();
}



void Adventure::hookupInputManagerListener(Listener* listener) {
   scene.hookupInputManagerListener(listener);
}
