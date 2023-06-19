#include "Adventure/Adventure.h"
#include "Algorithms/FoV.h"
#include "Enums/PlayerCommands.h"
#include "Logs/DebugLogger.h"
#include "SDL_keycode.h"


void Adventure::setListeners(Listener* gameWindowListener) {
   this->gameWindowListener =  gameWindowListener;
}


void Adventure::initScene() {
   scene->initialize(&effectDescriber);
   linkPlayerAndScene();
   scene->hookupListeners(gameWindowListener, (Listener*) &playerMan);
}

void Adventure::initialize() {
   switch (sceneIndex) {
   case 0:
      scenes[sceneIndex] = Scene(&log, &playerMan, 100, 100);
      scene = &scenes[sceneIndex];
      initScene();
      playerMan.armPlayer();
      log.sendMessage("You are </gold:Arta\\>, a fledgling adventurer recently arrived in the town of </brown:Murvell\\>. Here the townsfolk whisper fearfully of a dark cult inhabiting the town's catacombs; of a tribe of twisted once-humans feeding on the bodies interred along the dark tunnels they call home.\n</darkishred:You have decided to investigate.\\>\n");
      break;

   case 1:
      scenes[sceneIndex] = Scene(&log, &playerMan, 80, 80);
      scene = &scenes[sceneIndex];
      initScene();
      log.sendMessage("\nYou exit the tunnel into a large, mossy </darkgreen:Cavern\\>.\n");
      break;

   case 2:
      scenes[sceneIndex] = Scene(&log, &playerMan, 50, 50);
      scene = &scenes[sceneIndex];
      initScene();
      log.sendMessage("\nYou squeeze through the opening into an offshoot of the main cavern.\n");
      break;

   default:
      DebugLogger::log("AAAAAAAAAAAAAAAAAAAAA");
      break;
   }

   terrainGenerator.makeFloor(sceneIndex, scene);

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
      if ((modification&KMOD_SHIFT)==KMOD_LSHIFT || (modification&KMOD_SHIFT) == KMOD_RSHIFT) {
         if (playerMan.attemptLevelChange() == true) {
            newScene();
         }
      }
      else {
         needToRunTurn = playerMan.pickUpItem();
      }
   }

   else if (command == PC_WAIT) {
      if ((modification&KMOD_SHIFT)==KMOD_LSHIFT || (modification&KMOD_SHIFT) == KMOD_RSHIFT) {
         needToRunTurn = playerMan.startLongWait();
      }
      else {
         playerMan.waitTurn();
         needToRunTurn = true;
      }
   }

   else if (command == PC_USE_ABILITY) {
      needToRunTurn = playerMan.doAbility();
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
   if (sceneIndex >= NUM_SCENES) {
      log.sendMessage("Last floor");
      return;
   }

   sceneIndex++;
   initialize();
}

void Adventure::linkPlayerAndScene() {
   playerMan.setSceneDependencies(scene->getActorManager(), scene->getMap(), scene->getEffectManager(), scene->getItemManager(), scene->getItemFactory(), scene->getActorUtils(), scene->getAbilityManager());
}
