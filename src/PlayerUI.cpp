#include "Interface/UIScreens/PlayerUI.h"
#include "Entities/Actors/Inventory.h"

void PlayerUI::initialize(Adventure* adventure, SDL_Renderer* renderer, SDL_Texture* spritesheet) {
   this->playerMan = adventure->getPlayerManager();

   itemDescriber.initialize(adventure->getEffectDescriber());
   actorDescriber.initialize(adventure->getEffectDescriber());

	this->renderer = renderer;
	this->spritesheet = spritesheet;

   scroller.initialize(renderer, spritesheet);
   scroller.setMarginAndScrollMulitplier(textSpecs.margin, textSpecs.fontSizePixels);

   title = textMaker.makeGameText("Player Info");
   statsTitle = textMaker.makeGameText("Stats");
   weaponTitle = textMaker.makeGameText("Wielding");
   armorTitle = textMaker.makeGameText("Wearing");
}

void PlayerUI::render(const SDL_Rect& viewport) {
	SDL_RenderSetViewport(renderer, &viewport);
   currViewport = viewport;

   scroller.clear();

   textSpecs.setViewportWidth(viewport.w);
   textSpecsTitle.setViewportWidth(viewport.w);

   ActorEntity* player = playerMan->getPlayer();
   Inventory* inventory = &player->inventory;

   GameText health = textMaker.makeGameText(player->stats.getHealthAsString());
   GameText strength = textMaker.makeGameText(player->stats.getStrengthAsString());
   GameText intelligence = textMaker.makeGameText(player->stats.getIntelligenceAsString());
   GameText speed = textMaker.makeGameText(player->stats.getSpeedAsString());
   GameText weaponDesc = textMaker.makeGameText(itemDescriber.describeMinusDesc(inventory->getMeleeWeapon()));
   GameText magicWeaponDesc = textMaker.makeGameText(itemDescriber.describeMinusDesc(inventory->getMagicWeapon()));
   GameText armorDesc = textMaker.makeGameText(itemDescriber.describeMinusDesc(inventory->getArmor()));
   GameText effects = textMaker.makeGameText(actorDescriber.listEffects(player));

   scroller.setSpecsForSubsequentItems(textSpecsTitle);
   scroller.addItem(title);
   scroller.addItem(textSpecsTitle.messageSpacing);

   scroller.setSpecsForSubsequentItems(textSpecs);
   scroller.addItem(statsTitle);
   scroller.addItem(textSpecs.messageSpacing);
   scroller.addItem(health);
   scroller.addItem(textSpecs.messageSpacing);
   scroller.addItem(strength);
   scroller.addItem(textSpecs.messageSpacing);
   scroller.addItem(intelligence);
   scroller.addItem(textSpecs.messageSpacing);
   scroller.addItem(speed);

   scroller.addItem(3*textSpecs.messageSpacing);
   scroller.addItem(weaponTitle);
   scroller.addItem(textSpecs.messageSpacing);
   scroller.addItem(weaponDesc);
   scroller.addItem(2*textSpecs.lineSpacing);
   scroller.addItem(magicWeaponDesc);

   if (player->inventory.hasArmor()) {
      scroller.addItem(3*textSpecs.messageSpacing);
      scroller.addItem(armorTitle);
      scroller.addItem(textSpecs.messageSpacing);
      scroller.addItem(armorDesc);
   }

   scroller.addItem(3*textSpecs.messageSpacing);
   scroller.addItem(effects);

   scroller.render(viewport);

   /*
   int startY = textSpecs.margin;
   startY = textRenderer.renderGameText(textSpecsTitle, title, startY);
   startY += textSpecsTitle.messageSpacing;

   startY = textRenderer.renderGameText(textSpecs, health, startY);
   startY += 2*textSpecs.messageSpacing;
   startY = textRenderer.renderGameText(textSpecs, strength, startY);
   startY += textSpecs.messageSpacing;
   startY = textRenderer.renderGameText(textSpecs, intelligence, startY);
   startY += 2*textSpecs.messageSpacing;
   startY = textRenderer.renderGameText(textSpecs, speed, startY);

   startY += 3*textSpecs.messageSpacing;
   startY = textRenderer.renderGameText(textSpecs, weaponTitle, startY);
   startY += textSpecs.messageSpacing;
   startY = textRenderer.renderGameText(textSpecs, weaponDesc, startY);
   startY += textSpecs.messageSpacing;
   startY = textRenderer.renderGameText(textSpecs, magicWeaponDesc, startY);

   if (player->inventory.hasArmor()) {
      startY += 3*textSpecs.messageSpacing;
      startY = textRenderer.renderGameText(textSpecs, armorTitle, startY);
      startY += textSpecs.messageSpacing;
      startY = textRenderer.renderGameText(textSpecs, armorDesc, startY);
   }

   startY += 3*textSpecs.messageSpacing;
   startY = textRenderer.renderGameText(textSpecs, effects, startY);
   */
}



void PlayerUI::processScroll(int x, int y, int offset) {
	SDL_Point point = { x,y };
	if (SDL_PointInRect(&point, &currViewport)) {
      scroller.processScroll(offset);
   }
}
