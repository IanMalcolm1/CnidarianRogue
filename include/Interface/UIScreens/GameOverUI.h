#pragma once

#include "Interface/UIScreens/TwoButtonPopupUI.h"
#include <cctype>


/* This class should be listened to by Game */
class GameOverUI : public TwoButtonPopupUI {
private:
   void onLeftButtonSelect() override;
   void onRightButtonSelect() override;

public:
	GameOverUI(int fontSize = 2) :
   TwoButtonPopupUI("Game Over", "Restart", "Quit", fontSize) {};

   void processKeyPress(SDL_Keycode keycode);
};
