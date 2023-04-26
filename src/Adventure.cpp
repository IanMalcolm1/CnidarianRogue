#include "Adventure/Adventure.h"
#include "PlayerManager/PlayerManager.h"

void Adventure::linkPlayerAndScene() {
   playerMan.setSceneDependencies(scene.getTurnQueue(), scene.getMap(), scene.getInputConfirmer());
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
   scene.processCommand(command, modification);
}
void Adventure::runTurnIfAutoMoving() {
   scene.runTurnIfAutoMoving();
}
void Adventure::updateMapDisplay() {
   scene.updateMapDisplay();
}
