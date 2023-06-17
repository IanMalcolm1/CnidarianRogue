#pragma once

#include "Algorithms/TerrainGenerator.h"
#include "Adventure/Scene/Scene.h"
#include "Entities/Effects/EffectDescriber.h"
#include "EventListener/Listener.h"
#include "Logs/GameLog.h"
#include "Adventure/PlayerManager.h"
#include "Interface/InputConfirmer.h"
#include <cwchar>

#define NUM_SCENES 3

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

   void initScene();
   void linkPlayerAndScene();
   void newScene();

public:
   Adventure() : sceneIndex(0), scene(nullptr), alreadyRanTurn(false),
   playerMan(&log), scenes(NUM_SCENES, Scene(&log, &playerMan)) {};

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
