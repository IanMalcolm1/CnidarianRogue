#pragma once

#include "Algorithms/TerrainGenerator.h"
#include "Adventure/Scene/Scene.h"
#include "Entities/Effects/EffectDescriber.h"
#include "EventListener/Listener.h"
#include "Logs/GameLog.h"
#include "Adventure/PlayerManager.h"
#include "Interface/InputConfirmer.h"
#include <cwchar>


class Adventure {
private:
   std::vector<Scene> scenes;
   Scene* scene;
   int sceneIndex;

   TerrainGenerator terrainGenerator;
   GameLog log;
   PlayerManager playerMan;
   EffectDescriber effectDescriber;

   Listener* gameWindowListener;

   bool alreadyRanTurn;

   void linkPlayerAndScene();
   void newScene();

public:
   Adventure() : log(), sceneIndex(0), scene(nullptr), alreadyRanTurn(false),
   playerMan(&log), terrainGenerator(), scenes(3, Scene(&log, &playerMan)) {};

   void setListeners(Listener* gameWindowListener);
   void initialize();

   Scene* getScene();

   GameLog* getGameLog();
   PlayerManager* getPlayerManager();
   EffectDescriber* getEffectDescriber();

	void processCommand(PlayerCommand command, Uint16 modification);

   void runTurnIfAutoMoving();
	void updateMapDisplay();

};
