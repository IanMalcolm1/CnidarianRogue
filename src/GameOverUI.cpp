#include "Interface/UIScreens/GameOverUI.h"
#include "EventListener/Listener.h"
#include "GraphicsThings/RectFiller.h"


void GameOverUI::initialize(Listener* gameListener, SDL_Renderer* renderer, SDL_Texture* spritesheet) {
   this->renderer = renderer;
   this->spritesheet = spritesheet;
   addListener(gameListener);

   textRenderer.initialize(renderer, spritesheet);

   gameOverText = textMaker.makeGameText("Game Over");
   restartText = textMaker.makeGameText("Restart");
   quitText = textMaker.makeGameText("Quit");
}


void GameOverUI::render(const SDL_Rect& viewport) {
   if (hidden) { return; }

   if (viewport.w != parentViewport.w || viewport.h != parentViewport.h) {
		calcDimensions(viewport);
	}

	SDL_RenderSetViewport(renderer, &parentViewport);

	//gray out everything else
	SDL_SetTextureAlphaMod(spritesheet, 128);
	RectFiller::fill(renderer, spritesheet, viewport, { 0,0,0 });

	//black background for screen
	SDL_SetTextureAlphaMod(spritesheet, 255);
	RectFiller::fill(renderer, spritesheet, screenViewport, { 0,0,0 });

	//highlights
	if (highlightRestart) {
		SDL_SetTextureAlphaMod(spritesheet, 128);
		RectFiller::fill(renderer, spritesheet, restartViewport, { 255, 255, 0 });
	}
	else if (highlightQuit) {
		SDL_SetTextureAlphaMod(spritesheet, 128);
		RectFiller::fill(renderer, spritesheet, quitViewport, { 255, 0, 0 });
	}
	SDL_SetTextureAlphaMod(spritesheet, 255);


	//main message
	SDL_RenderSetViewport(renderer, &screenViewport);
	textSpecs.setViewportWidth(screenViewport.w);
	textRenderer.renderGameText(textSpecs, gameOverText, textSpecs.margin, TEXT_ALIGN_CENTER | TEXT_RENDER_DOWN);

	//yes
	SDL_RenderSetViewport(renderer, &restartViewport);
	textSpecs.setViewportWidth(restartViewport.w);
	textRenderer.renderGameText(textSpecs, restartText, textSpecs.margin, TEXT_ALIGN_CENTER | TEXT_RENDER_DOWN);

	//no
	SDL_RenderSetViewport(renderer, &quitViewport);
	textSpecs.setViewportWidth(quitViewport.w);
	textRenderer.renderGameText(textSpecs, quitText, textSpecs.margin, TEXT_ALIGN_CENTER | TEXT_RENDER_DOWN);

	//borders
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderSetViewport(renderer, &parentViewport);
	SDL_RenderDrawRect(renderer, &restartViewport);
	SDL_RenderDrawRect(renderer, &quitViewport);
	SDL_RenderDrawRect(renderer, &screenViewport);


	highlightQuit = highlightRestart = false;
}


void GameOverUI::processMouseLocation(int x, int y) {
   if (hidden) {
		return;
	}

	SDL_Point point = { x,y };
	if (!SDL_PointInRect(&point, &screenViewport)) {
		return;
	}

	if (SDL_PointInRect(&point, &restartViewport)) {
		highlightRestart = true;
	}
	else if (SDL_PointInRect(&point, &quitViewport)) {
		highlightQuit = true;
	}
}

void GameOverUI::processMouseClick(int x, int y) {
   if (hidden) {
		return;
	}

	SDL_Point point = { x,y };
	if (SDL_PointInRect(&point, &restartViewport)) {
		hidden = true;
      notifyListeners(EVENT_RESTART_GAME);
	}
	else if (SDL_PointInRect(&point, &quitViewport)) {
		hidden = true;
      notifyListeners(EVENT_QUIT_GAME);
	}
}

void GameOverUI::processKeyPress(SDL_Keycode keycode) {
	if (hidden) {
		return;
	}

	if (keycode == SDLK_r) {
      hidden = true;
      notifyListeners(EVENT_RESTART_GAME);
	}
	else if (keycode == SDLK_q || keycode == SDLK_ESCAPE) {
      hidden = true;
      notifyListeners(EVENT_QUIT_GAME);
	}
}

void GameOverUI::calcDimensions(const SDL_Rect& viewport) {
	parentViewport.w = viewport.w;
	parentViewport.h = viewport.h;

	screenViewport.w = 2*textSpecs.margin + textSpecs.fontSizePixels*20;
	screenViewport.h = 2*textSpecs.margin + textSpecs.fontSizePixels*12;
	screenViewport.x = (parentViewport.w - screenViewport.w) / 2;
	screenViewport.y = (parentViewport.h - screenViewport.h) / 2;

	restartViewport.h = quitViewport.h = textSpecs.fontSizePixels + 2 * textSpecs.margin;
	restartViewport.w = quitViewport.w = textSpecs.fontSizePixels*7 + 2*textSpecs.margin;

	restartViewport.x = screenViewport.x + screenViewport.w/4 - restartViewport.w/2;
	quitViewport.x = screenViewport.x + 3*screenViewport.w/4 - quitViewport.w/2;

	restartViewport.y = quitViewport.y = screenViewport.y + screenViewport.h - (16 + restartViewport.h);
}
