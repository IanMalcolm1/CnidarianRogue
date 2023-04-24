#pragma once

#include "Scene/Scene.h"
#include "Logs/GameLog.h"
#include "PlayerManager/PlayerManager.h"
#include "UIScreens/InputConfirmer.h"


class Adventure {
private:
   Scene scene;
   GameLog log;
   PlayerManager playerMan;

   InputConfirmer confirmer;

   void linkPlayerAndScene();
public:
   Adventure() : log(GameLog()),
      playerMan(PlayerManager()),
      scene(Scene(&log, &playerMan)) {};


   void changeScene();
};
