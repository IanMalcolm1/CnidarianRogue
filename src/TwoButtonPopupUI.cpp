#include "Interface/UIScreens/TwoButtonPopupUI.h"
#include "EventListener/Listener.h"
#include "GraphicsThings/SDLHelper.h"


void TwoButtonPopupUI::initialize(Listener* gameListener, SDL_Renderer* renderer, SDL_Texture* spritesheet) {
   this->renderer = renderer;
   this->spritesheet = spritesheet;
   addListener(gameListener);

   textRenderer.initialize(renderer, spritesheet);
}


void TwoButtonPopupUI::render(const SDL_Rect& viewport) {
   if (hidden) { return; }

   if (viewport.w != parentViewport.w || viewport.h != parentViewport.h) {
		calcDimensions(viewport);
	}

	SDL_RenderSetViewport(renderer, &parentViewport);

	//gray out everything else
	SDL_SetTextureAlphaMod(spritesheet, 128);
	SDLHelper::fillRect(renderer, spritesheet, viewport, { 0,0,0 });

	//black background for screen
	SDL_SetTextureAlphaMod(spritesheet, 255);
	SDLHelper::fillRect(renderer, spritesheet, screenViewport, { 0,0,0 });

	//highlights
	if (highlightLeftButton) {
		SDL_SetTextureAlphaMod(spritesheet, 128);
		SDLHelper::fillRect(renderer, spritesheet, leftButtonViewport, { 255, 255, 0 });
	}
	else if (highlightRightButton) {
		SDL_SetTextureAlphaMod(spritesheet, 128);
		SDLHelper::fillRect(renderer, spritesheet, rightButtonViewport, { 255, 0, 0 });
	}
	SDL_SetTextureAlphaMod(spritesheet, 255);


	//main message
	SDL_RenderSetViewport(renderer, &screenViewport);
	textSpecs.setViewportWidth(screenViewport.w);
	textRenderer.renderGameText(textSpecs, mainText, textSpecs.margin, TEXT_ALIGN_CENTER | TEXT_RENDER_DOWN);

	//yes
	SDL_RenderSetViewport(renderer, &leftButtonViewport);
	textSpecs.setViewportWidth(leftButtonViewport.w);
	textRenderer.renderGameText(textSpecs, leftText, textSpecs.margin, TEXT_ALIGN_CENTER | TEXT_RENDER_DOWN);

	//no
	SDL_RenderSetViewport(renderer, &rightButtonViewport);
	textSpecs.setViewportWidth(rightButtonViewport.w);
	textRenderer.renderGameText(textSpecs, rightText, textSpecs.margin, TEXT_ALIGN_CENTER | TEXT_RENDER_DOWN);

	//borders
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderSetViewport(renderer, &parentViewport);
	SDL_RenderDrawRect(renderer, &leftButtonViewport);
	SDL_RenderDrawRect(renderer, &rightButtonViewport);
	SDL_RenderDrawRect(renderer, &screenViewport);


	highlightRightButton = highlightLeftButton = false;
}


void TwoButtonPopupUI::processMouseLocation(int x, int y) {
   if (hidden) {
		return;
	}

	SDL_Point point = { x,y };
	if (!SDL_PointInRect(&point, &screenViewport)) {
		return;
	}

	if (SDL_PointInRect(&point, &leftButtonViewport)) {
		highlightLeftButton = true;
	}
	else if (SDL_PointInRect(&point, &rightButtonViewport)) {
		highlightRightButton = true;
	}
}


void TwoButtonPopupUI::setMessage(std::string message) {
   GameTextMaker textMaker = GameTextMaker();
   mainText = textMaker.makeGameText(message);
}


void TwoButtonPopupUI::processMouseClick(int x, int y) {
   if (hidden) {
		return;
	}

	SDL_Point point = { x,y };
	if (SDL_PointInRect(&point, &leftButtonViewport)) {
      onLeftButtonSelect();
		hidden = true;
	}
	else if (SDL_PointInRect(&point, &rightButtonViewport)) {
      onRightButtonSelect();
		hidden = true;
	}
}

void TwoButtonPopupUI::onLeftButtonSelect() {
   return;
}
void TwoButtonPopupUI::onRightButtonSelect() {
   return;
}

void TwoButtonPopupUI::calcDimensions(const SDL_Rect& viewport) {
	parentViewport.w = viewport.w;
	parentViewport.h = viewport.h;

	screenViewport.w = 2*textSpecs.margin + textSpecs.fontSizePixels*20;
	screenViewport.h = 2*textSpecs.margin + textSpecs.fontSizePixels*12;
	screenViewport.x = (parentViewport.w - screenViewport.w) / 2;
	screenViewport.y = (parentViewport.h - screenViewport.h) / 2;

	leftButtonViewport.h = rightButtonViewport.h = textSpecs.fontSizePixels + 2 * textSpecs.margin;
	leftButtonViewport.w = rightButtonViewport.w = textSpecs.fontSizePixels*buttonLength + 2*textSpecs.margin;

	leftButtonViewport.x = screenViewport.x + screenViewport.w/4 - leftButtonViewport.w/2;
	rightButtonViewport.x = screenViewport.x + 3*screenViewport.w/4 - rightButtonViewport.w/2;

	leftButtonViewport.y = rightButtonViewport.y = screenViewport.y + screenViewport.h - (16 + leftButtonViewport.h);
}
