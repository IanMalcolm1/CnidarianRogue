#include "Interface/UIScreens/LookUI.h"
#include "GraphicsThings/TextRenderer.h"


void LookUI::initialize(Adventure* adventure, SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	this->renderer = renderer;
	this->spritesheet = spritesheet;

   itemDescriber.initialize(adventure->getEffectDescriber());
   actorDescriber.initialize(adventure->getEffectDescriber());

   textRenderer.initialize(renderer, spritesheet);
   
   titleText = textMaker.makeGameText("Tile Info");
   defaultText = textMaker.makeGameText("There's nothing here.");
}


void LookUI::render(Scene* scene, const SDL_Rect& viewport) {
   //TODO: add scrolling (maybe)
   this->map = scene->getMap();
   terrainDescriber.setMap(map);


	SDL_RenderSetViewport(renderer, &viewport);
   
   textSpecs.setViewportWidth(viewport.w);
   textSpecsTitle.setViewportWidth(viewport.w);

   TileCoords focusTile = map->getFocusTileLocation();
   int startY = textSpecs.margin;
   std::vector<GameText> descriptions;

   startY = textRenderer.renderGameText(textSpecsTitle, titleText, startY);
   startY += textSpecsTitle.messageSpacing;

   if (!map->getMapDisplay()->isVisible(map->coordsToTileIndex(focusTile))) {
      textRenderer.renderGameText(textSpecs, defaultText, startY);
      return;
   }

   GameText terrainText = textMaker.makeGameText(terrainDescriber.describeTerrainAt(focusTile));
   startY = textRenderer.renderGameText(textSpecs, terrainText, startY);
   startY += textSpecs.messageSpacing;


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
      startY = textRenderer.renderGameText(textSpecs, descriptions[i], startY);
      if (i != descriptions.size()-1) {
         startY = textRenderer.renderLineSeparator(textSpecs, textMaker, startY);
      }
   }
}
