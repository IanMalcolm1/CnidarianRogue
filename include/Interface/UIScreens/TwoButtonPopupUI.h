#pragma once

#include "GraphicsThings/GameText.h"
#include "GraphicsThings/TextRenderer.h"
#include "EventListener/Blabber.h"
#include <SDL.h>
#include <algorithm>


class TwoButtonPopupUI : public Blabber {
private:
	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

	TextRenderer textRenderer;
	TextRenderingSpecs textSpecs;

   int buttonLength;
	GameText mainText, leftText, rightText;
	SDL_Rect parentViewport;
	SDL_Rect screenViewport, leftButtonViewport, rightButtonViewport;

	bool highlightRightButton, highlightLeftButton;

	void calcDimensions(const SDL_Rect& viewport);

   virtual void onLeftButtonSelect();
   virtual void onRightButtonSelect();

public:
	bool hidden;

	TwoButtonPopupUI(std::string mainText, std::string leftText,
   std::string rightText, int fontSize = 4) : renderer(NULL), spritesheet(NULL),
   parentViewport(), leftButtonViewport(), rightButtonViewport(),
   screenViewport(), highlightLeftButton(false), highlightRightButton(false),
   textRenderer(), textSpecs(fontSize), hidden(true) {
      buttonLength = std::max(leftText.size(), rightText.size());
	   GameTextMaker textMaker = GameTextMaker();
      this->mainText = textMaker.makeGameText(mainText);
      this->leftText = textMaker.makeGameText(leftText);
      this->rightText = textMaker.makeGameText(rightText);
   };

	void initialize(Listener* listener, SDL_Renderer* renderer, SDL_Texture* spritesheet);

	void render(const SDL_Rect& viewport);

	void processMouseLocation(int x, int y);
	void processMouseClick(int x, int y);
};
