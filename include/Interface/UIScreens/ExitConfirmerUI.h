#pragma once

#include "Interface/UIScreens/TwoButtonPopupUI.h"
#include <cctype>


/* This class should be listened to by Game */
class ExitConfirmerUI : public TwoButtonPopupUI {
private:
   void onLeftButtonSelect() override;
   void onRightButtonSelect() override;

public:
	ExitConfirmerUI(int fontSize = 2) :
   TwoButtonPopupUI("Quit Game?", "Yes", "No", fontSize) {};

   void processKeyPress(SDL_Keycode keycode);
};
