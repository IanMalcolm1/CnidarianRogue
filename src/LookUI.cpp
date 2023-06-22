#include "Interface/UIScreens/LookUI.h"
#include "GraphicsThings/TextRenderer.h"
#include <cwctype>


void LookUI::initialize(Adventure* adventure, SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	this->renderer = renderer;
	this->spritesheet = spritesheet;

   itemDescriber.initialize(adventure->getEffectDescriber());
   actorDescriber.initialize(adventure->getEffectDescriber());

   scroller.initialize(renderer, spritesheet);
   scroller.setMarginAndScrollMulitplier(textSpecs.margin, textSpecs.fontSizePixels);
   
   titleText = textMaker.makeGameText("Tile Info");
   defaultText = textMaker.makeGameText("There's nothing here.");
}


void LookUI::render(Scene* scene, const SDL_Rect& viewport) {
   //TODO: add scrolling (maybe)
   this->map = scene->getMap();
   terrainDescriber.setMap(map);


	SDL_RenderSetViewport(renderer, &viewport);
   scroller.clear();
   
   textSpecs.setViewportWidth(viewport.w);
   textSpecsTitle.setViewportWidth(viewport.w);

   TileCoords focusTile = map->getFocusTileLocation();
   int startY = textSpecs.margin;
   std::vector<GameText> descriptions;

   scroller.setSpecsForSubsequentItems(textSpecsTitle);
   scroller.addItem(titleText);
   scroller.addItem(textSpecsTitle.messageSpacing);
   scroller.setSpecsForSubsequentItems(textSpecs);

   if (!map->getMapDisplay()->isVisible(map->coordsToTileIndex(focusTile))) {
      scroller.addItem(defaultText);
      scroller.render(viewport);
      return;
   }

   GameText terrainText = textMaker.makeGameText(terrainDescriber.describeTerrainAt(focusTile));
   scroller.addItem(terrainText);
   scroller.addItem(textSpecs.messageSpacing);

   if (map->thereIsAnActorAt(focusTile)) {
      ActorEntity* actor = map->getActorAt(focusTile);
      GameText desc = textMaker.makeGameText(actorDescriber.describe(actor));
      descriptions.push_back(desc);
   }
   if (map->getItemsAt(focusTile)->size() != 0) {
      for (auto item : (*map->getItemsAt(focusTile))) {
         GameText desc = textMaker.makeGameText(itemDescriber.describe(item));
         descriptions.push_back(desc);
      }
   }

   
   for (int i=0; i<descriptions.size(); i++) {
      scroller.addItem(descriptions[i]);
      if (i != descriptions.size()-1) {
         scroller.addLineSeparator();
      }
   }

   scroller.render(viewport);
}


void LookUI::processScroll(int x, int y, int offset, bool ctrlDown) {
   if (ctrlDown) {
      if ((offset<0 && textSpecs.fontSize>1) || (offset>0 && textSpecsTitle.fontSize<10)) {
         textSpecs.modifyFontSize(offset);
         textSpecsTitle.modifyFontSize(offset);
      }
   }
   else {
      scroller.processScroll(x, y, offset);
   }
}
