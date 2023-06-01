#include "Interface/UIScreens/ConfirmerUI.h"
#include "GraphicsThings/SDLHelper.h"


void ConfirmerUI::initialize(InputConfirmer* signaller, SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	this->renderer = renderer;
	this->spritesheet = spritesheet;

	this->signaller = signaller;

	textRenderer.initialize(renderer, spritesheet);

	yes = textMaker.makeGameText("Yes");
	no = textMaker.makeGameText("No");
}

void ConfirmerUI::render(const SDL_Rect& viewport) {
	if (!signaller->isAwaiting()) {
		return;
	}
	else {
		hidden = false;
	}

	if (viewport.w != parentViewport.w || viewport.h != parentViewport.h) {
		calcDimensions(viewport);
	}

	SDL_RenderSetViewport(renderer, &parentViewport);

	//gray out everything else
	SDL_SetTextureAlphaMod(spritesheet, 128);
	SDLHelper::fill(renderer, spritesheet, viewport, { 0,0,0 });

	//black background for screen
	SDL_SetTextureAlphaMod(spritesheet, 255);
	SDLHelper::fill(renderer, spritesheet, screenViewport, { 0,0,0 });

	//highlights
	if (highlightYes) {
		SDL_SetTextureAlphaMod(spritesheet, 128);
		SDLHelper::fill(renderer, spritesheet, yesViewport, { 0, 255, 0 });
	}
	else if (highlightNo) {
		SDL_SetTextureAlphaMod(spritesheet, 128);
		SDLHelper::fill(renderer, spritesheet, noViewport, { 255, 0, 0 });
	}
	SDL_SetTextureAlphaMod(spritesheet, 255);


	//main message
	SDL_RenderSetViewport(renderer, &screenViewport);
	textSpecs.setViewportWidth(screenViewport.w);
	GameText message = textMaker.makeGameText(signaller->message);
	textRenderer.renderGameText(textSpecs, message, textSpecs.margin, TEXT_ALIGN_CENTER | TEXT_RENDER_DOWN);

	//yes
	SDL_RenderSetViewport(renderer, &yesViewport);
	textSpecs.setViewportWidth(yesViewport.w);
	textRenderer.renderGameText(textSpecs, yes, textSpecs.margin, TEXT_ALIGN_CENTER | TEXT_RENDER_DOWN);

	//no
	SDL_RenderSetViewport(renderer, &noViewport);
	textSpecs.setViewportWidth(noViewport.w);
	textRenderer.renderGameText(textSpecs, no, textSpecs.margin, TEXT_ALIGN_CENTER | TEXT_RENDER_DOWN);

	//borders
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderSetViewport(renderer, &parentViewport);
	SDL_RenderDrawRect(renderer, &yesViewport);
	SDL_RenderDrawRect(renderer, &noViewport);
	SDL_RenderDrawRect(renderer, &screenViewport);


	highlightNo = highlightYes = false;
}

void ConfirmerUI::processMouseLocation(int x, int y) {
	if (hidden) {
		return;
	}

	SDL_Point point = { x,y };
	if (!SDL_PointInRect(&point, &screenViewport)) {
		return;
	}

	if (SDL_PointInRect(&point, &yesViewport)) {
		highlightYes = true;
	}
	else if (SDL_PointInRect(&point, &noViewport)) {
		highlightNo = true;
	}
}

void ConfirmerUI::processMouseClick(int x, int y) {
	if (hidden) {
		return;
	}

	SDL_Point point = { x,y };
	if (SDL_PointInRect(&point, &yesViewport)) {
		signaller->setConfirmation(1);
		hidden = true;
	}
	else if (SDL_PointInRect(&point, &noViewport)) {
		signaller->setConfirmation(0);
		hidden = true;
	}
}

void ConfirmerUI::processKeyPress(SDL_Keycode keycode) {
	if (hidden) {
		return;
	}

	if (keycode == SDLK_y) {
		signaller->setConfirmation(1);
		hidden = true;
	}
	else if (keycode == SDLK_n || keycode == SDLK_ESCAPE) {
		signaller->setConfirmation(0);
		hidden = true;
	}
}


void ConfirmerUI::calcDimensions(const SDL_Rect& viewport) {
	parentViewport.w = viewport.w;
	parentViewport.h = viewport.h;

	screenViewport.w = 2*textSpecs.margin + textSpecs.fontSizePixels*20;
	screenViewport.h = 2*textSpecs.margin + textSpecs.fontSizePixels*12;
	screenViewport.x = (parentViewport.w - screenViewport.w) / 2;
	screenViewport.y = (parentViewport.h - screenViewport.h) / 2;

	yesViewport.h = noViewport.h = textSpecs.fontSizePixels + 2 * textSpecs.margin;
	yesViewport.w = noViewport.w = textSpecs.fontSizePixels*3 + 2*textSpecs.margin;

	yesViewport.x = screenViewport.x + screenViewport.w/4 - yesViewport.w/2;
	noViewport.x = screenViewport.x + 3*screenViewport.w/4 - noViewport.w/2;

	yesViewport.y = noViewport.y = screenViewport.y + screenViewport.h - (16 + yesViewport.h);
}
