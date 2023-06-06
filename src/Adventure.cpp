#include "Adventure/Adventure.h"
#include "Algorithms/FoV.h"
#include "Enums/PlayerCommands.h"
#include "SDL_keycode.h"


void Adventure::setListeners(Listener* gameWindowListener) {
   this->gameWindowListener =  gameWindowListener;
}

void Adventure::initialize() {
   scene = &scenes[sceneIndex];
   scene->initialize(&effectDescriber);
   linkPlayerAndScene();
   scene->hookupListeners(gameWindowListener, (Listener*) &playerMan);
   terrainGenerator.rectangleRooms(scene, 30, 30);
   FoV::calcPlayerFoV(scene->getMap(), playerMan.getPlayer());
   updateMapDisplay();
}

Scene* Adventure::getScene() {
   return scene;
}


GameLog* Adventure::getGameLog() {
   return &log;
}
PlayerManager* Adventure::getPlayerManager() {
   return &playerMan;
}
EffectDescriber* Adventure::getEffectDescriber() {
   return &effectDescriber;
}


void Adventure::processCommand(PlayerCommand command, Uint16 modification) {
	bool needToRunTurn = false;

	if (playerMan.isAutoActing()) {
		if (command == PC_ESCAPEKEY) {
			playerMan.clearAutoAct();
			return;
		}
		needToRunTurn = playerMan.doAutoAct();
      if (needToRunTurn) {
         scene->runTurn();
      }
		return;
	}


   if (command < 9) { //process player move
      needToRunTurn = playerMan.processDirectionalCommand(command);
   }

   else if (command == PC_PICKUP) {
      needToRunTurn = playerMan.pickUpItem();
   }

   else if (command == PC_WAIT) {
      if ((modification&KMOD_SHIFT)==KMOD_LSHIFT || (modification&KMOD_SHIFT) == KMOD_RSHIFT) {
         if (playerMan.attemptLevelChange() == true) {
            newScene();
         }
      }
      else {
         playerMan.waitTurn();
         needToRunTurn = true;
      }
   }

   else if (command == PC_CONFIRM) {
      needToRunTurn = playerMan.processConfirm();
   }

   else if (command == PC_TOGGLE_LOOK || command == PC_TOGGLE_SELECT) {
      playerMan.updateInputState(command);
   }

   else if (command == PC_ESCAPEKEY) {
      playerMan.resetInputState();
   }

   if (needToRunTurn) {
      scene->runTurn();
   }
}


void Adventure::runTurnIfAutoMoving() {
	if (!alreadyRanTurn && playerMan.isAutoActing()) {
      bool needToRunTurn = playerMan.doAutoAct();
      if (needToRunTurn) {
         scene->runTurn();
      }
	}
	alreadyRanTurn = false;
}


void Adventure::updateMapDisplay() {
   scene->updateMapDisplay();
}


void Adventure::newScene() {
   if (sceneIndex >= scenes.size()-1) {
      log.sendMessage("Last floor");
      return;
   }

   sceneIndex++;
   initialize();
}

void Adventure::linkPlayerAndScene() {
   playerMan.setSceneDependencies(scene->getTurnQueue(), scene->getMap(), scene->getEffectManager(), scene->getItemManager(), scene->getItemFactory(), scene->getActorUtils());
}
