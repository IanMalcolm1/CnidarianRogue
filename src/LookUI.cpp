#include "Interface/UIScreens/LookUI.h"
#include "Topography/TileCoordinates.h"
#include <string>


void LookUI::initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	this->renderer = renderer;
	this->spritesheet = spritesheet;

   textRenderer.initialize(renderer, spritesheet);
   
   titleText = textMaker.makeGameText("Tile Info:");
   defaultText = textMaker.makeGameText("There's nothing here.");
}


void LookUI::render(const SDL_Rect& viewport) {
   //TODO: add scrolling  
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

      names.push_back(makeName(actor->description.name, actor->display));
      descriptions.push_back(textMaker.makeGameText(actor->description.desc));
      tileIsEmpty = false;
   }
   if (map->getItemsAt(focusTile)->size() != 0) {
      for (auto item : (*map->getItemsAt(focusTile))) {
         names.push_back(makeName(item->description.name, item->display));
         descriptions.push_back(textMaker.makeGameText(item->description.desc));
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


GameText LookUI::makeName(std::string name, EntityDisplay disp) {
   name.insert(0, "/> ");
   name.insert(0, std::string(1, (char)disp.symbol));
   name.insert(0, ":");

   std::string color = std::to_string(disp.symbolColor.b);
   if (color.size() < 3) { color.insert(0, "0"); }
   if (color.size() < 3) { color.insert(0, "0"); }
   name.insert(0, color);

   color = std::to_string(disp.symbolColor.g);
   if (color.size() < 3) { color.insert(0, "0"); }
   if (color.size() < 3) { color.insert(0, "0"); }
   name.insert(0, color);
   
   color = std::to_string(disp.symbolColor.r);
   if (color.size() < 3) { color.insert(0, "0"); }
   if (color.size() < 3) { color.insert(0, "0"); }
   name.insert(0, color);

   name.insert(0, "</");

   return textMaker.makeGameText(name);
}
