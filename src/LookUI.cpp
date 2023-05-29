#include "Interface/UIScreens/LookUI.h"
#include <string>


void LookUI::initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	this->renderer = renderer;
	this->spritesheet = spritesheet;

   textRenderer.initialize(renderer, spritesheet);
   
   titleText = textMaker.makeGameText("Tile Info:");
   defaultText = textMaker.makeGameText("There's nothing here.");

   /* I don't know why, but when restarting the game on the player's
    * death the constructor passed some random memory address waaaaay
    * off from where textMaker actually was. Caused a segfault.
    * Obviously has something to do with remaking the AdventureUI in
    * the GameWindow class. Maybe it puts stuff on the stack when
    * copying stuff and so gave the describers a pointer to the stack???
    * Very frustrating.
    */
   actorDescriber.setGameTextMaker(&textMaker);
   itemDescriber.setGameTextMaker(&textMaker);
}


void LookUI::render(const SDL_Rect& viewport) {
   //TODO: add scrolling (maybe)
	SDL_RenderSetViewport(renderer, &viewport);
   
   textSpecs.setViewportWidth(viewport.w);
   textSpecsTitle.setViewportWidth(viewport.w);

   TileCoords focusTile = map->getFocusTileLocation();
   int startY = textSpecs.margin;
   std::vector<GameText> names;
   std::vector<GameText> descriptions;
   bool tileIsEmpty = true;

   startY = textRenderer.renderGameText(textSpecsTitle, titleText, startY);
   startY += textSpecsTitle.messageSpacing;

   if (!map->getMapDisplay()->isVisible(map->coordsToTileIndex(focusTile))) {
      textRenderer.renderGameText(textSpecs, defaultText, startY);
      return;
   }

   if (map->thereIsAnActorAt(focusTile)) {
      ActorEntity* actor = map->getActorAt(focusTile);

      names.push_back(actorDescriber.name(actor));
      descriptions.push_back(actorDescriber.describe(actor));
      tileIsEmpty = false;
   }
   if (map->getItemsAt(focusTile)->size() != 0) {
      for (auto item : (*map->getItemsAt(focusTile))) {
         names.push_back(itemDescriber.name(item));
         descriptions.push_back(itemDescriber.describeInDepth(item));
      }
      tileIsEmpty = false;
   }

   if (tileIsEmpty) {
      textRenderer.renderGameText(textSpecs, defaultText, startY);
      return;
   }


   for (int i=0; i<names.size(); i++) {
      startY = textRenderer.renderGameText(textSpecs, names[i], startY);
      startY += textSpecs.messageSpacing;
      startY = textRenderer.renderGameText(textSpecs, descriptions[i], startY);
      startY += textSpecs.lineSpacing;
      if (i != names.size()-1) {
         startY = textRenderer.renderLineSeparator(textSpecs, textMaker, startY);
      }
   }
}
