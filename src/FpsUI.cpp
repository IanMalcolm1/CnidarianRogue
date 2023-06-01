#include "Interface/UIScreens/FpsUI.h"


void FpsUI::initialize(SDL_Renderer *renderer, SDL_Texture *spritesheet) {
   this->renderer = renderer;
   this->spritesheet = spritesheet;

   textRenderer.initialize(renderer, spritesheet);
}


void FpsUI::render(const SDL_Rect &screenDimensions, int fps) {
   if (hidden) {
      return;
   }

   updateViewport(screenDimensions);
	SDL_RenderSetViewport(renderer, &viewport);

   GameText fpsText = textMaker.makeGameText("FPS: "+std::to_string(fps));

   textRenderer.renderGameText(textSpecs, fpsText, textSpecs.margin);
}


void FpsUI::processKeyPress(SDL_Keycode keycode, SDL_Keymod modification) {
   //Toggled with CTRL+p
   if (keycode == SDLK_p && (modification&KMOD_LCTRL) == KMOD_LCTRL) {
      toggleHidden();
   }
}


void FpsUI::updateViewport(const SDL_Rect& screenDimensions) {
   viewport.w = 2*textSpecs.margin + 9*textSpecs.fontSizePixels;
   viewport.h = 2*textSpecs.margin + textSpecs.fontSizePixels;

   viewport.x = screenDimensions.w - viewport.w + 8;
   viewport.y = 8;

   textSpecs.setViewportWidth(viewport.w);
}

void FpsUI::toggleHidden() {
   hidden = hidden ? false : true;
}
