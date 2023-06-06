#include "Interface/UIScreens/PlayerUI.h"

void PlayerUI::initialize(Adventure* adventure, SDL_Renderer* renderer, SDL_Texture* spritesheet) {
   this->playerMan = adventure->getPlayerManager();

   itemDescriber.initialize(adventure->getEffectDescriber());
   actorDescriber.initialize(adventure->getEffectDescriber());

	this->renderer = renderer;
	this->spritesheet = spritesheet;

   textRenderer.initialize(renderer, spritesheet);

   title = textMaker.makeGameText("Player Info");
   weaponTitle = textMaker.makeGameText("Wielding:");
}

void PlayerUI::render(const SDL_Rect& viewport) {
	SDL_RenderSetViewport(renderer, &viewport);

   textSpecs.setViewportWidth(viewport.w);
   textSpecsTitle.setViewportWidth(viewport.w);

   ActorEntity* player = playerMan->getPlayer();
   GameText health = textMaker.makeGameText(player->stats.getHealthAsString());
   GameText strength = textMaker.makeGameText(player->stats.getStrengthAsString());
   GameText intelligence = textMaker.makeGameText(player->stats.getIntelligenceAsString());
   GameText speed = textMaker.makeGameText(player->stats.getSpeedAsString());
   GameText weaponDesc = textMaker.makeGameText(itemDescriber.describeWeapon(player->getPhysicalWeapon()));
   GameText magicWeaponDesc = textMaker.makeGameText(itemDescriber.describeWeapon(player->getMagicWeapon()));
   GameText effects = textMaker.makeGameText(actorDescriber.listEffects(player));

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

   startY += 3*textSpecs.messageSpacing;
   startY = textRenderer.renderGameText(textSpecs, effects, startY);
}
