#include "Interface/UIScreens/AdventureUI.h"


void AdventureUI::initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet) {
   this->renderer = renderer;
   this->spritesheet = spritesheet;

   sceneUI.initialize(renderer, spritesheet);
   messagesUI.initialize(renderer, spritesheet);
   playerUI.initialize(renderer, spritesheet);
}

void AdventureUI::render(const SDL_Rect& screenDimensions) {
   if (screenDimensions.h != viewports.fullscreen.h ||
      screenDimensions.w != viewports.fullscreen.w) {
      updateViewports(screenDimensions);
   }

   sceneUI.render(viewports.map);
   resetRendererAndDrawBorder(viewports.map);

   messagesUI.render(viewports.messages);
   resetRendererAndDrawBorder(viewports.messages);

   playerUI.render(viewports.player);
   resetRendererAndDrawBorder(viewports.player);
}

void AdventureUI::processCursorLocation(int x, int y) {
   sceneUI.processCursorLocation(x, y);
}
void AdventureUI::processScroll(int x, int y, int offset, bool ctrlDown) {
   sceneUI.processScroll(x, y, offset, ctrlDown);
   messagesUI.processScroll(x, y, offset, ctrlDown);
}
void AdventureUI::processClick(int x, int y, bool ctrlDown) {
   sceneUI.processClick(x, y, ctrlDown);
}
void AdventureUI::processKeyPress(SDL_Keycode keycode) {
   sceneUI.processKeyPress(keycode);
}




void AdventureUI::updateViewports(const SDL_Rect& screenDimensions) {
	int screenBorderSpacing = 5;
	int viewportSpacing = 8;

   viewports.fullscreen = screenDimensions;

	/* x-axis */
	viewports.player.x = screenBorderSpacing;
	viewports.player.w = (1 * screenDimensions.w / 5) - (screenBorderSpacing + viewportSpacing/2);

	viewports.map.x = (1 * screenDimensions.w / 5) + (viewportSpacing/2);
	viewports.map.w = (4 * screenDimensions.w / 5) - (screenBorderSpacing + viewportSpacing/2);

	viewports.messages.x = (1 * screenDimensions.w / 5) + (viewportSpacing/2);
	viewports.messages.w = (4 * screenDimensions.w / 5) - (screenBorderSpacing + viewportSpacing/2);

	/* y-axis */
	viewports.player.y = screenBorderSpacing;
	viewports.player.h = screenDimensions.h - (2*screenBorderSpacing);

	viewports.map.y = screenBorderSpacing;
	viewports.map.h = (4 * screenDimensions.h / 5) - (screenBorderSpacing + viewportSpacing/2);

	viewports.messages.y = (4 * screenDimensions.h / 5) + (viewportSpacing/2);
	viewports.messages.h = (1 * screenDimensions.h / 5) - (screenBorderSpacing + viewportSpacing/2);
}

void AdventureUI::resetRendererAndDrawBorder(SDL_Rect& currentViewport) {
	SDL_RenderSetViewport(renderer, &viewports.fullscreen);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &currentViewport);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetTextureAlphaMod(spritesheet, 255);
	SDL_SetTextureColorMod(spritesheet, 255, 255, 255);
}
