#include "Interface/UIScreens/PlayerUI.h"
#include "Adventure/PlayerManager.h"

void PlayerUI::initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	this->renderer = renderer;
	this->spritesheet = spritesheet;

   textRenderer.initialize(renderer, spritesheet);

   title = textMaker.makeGameText("Player Stats");
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
   GameText moveSpeed = textMaker.makeGameText(player->stats.getMoveSpeedAsString());
   GameText attackSpeed = textMaker.makeGameText(player->stats.getAttackSpeedAsString());
   GameText weaponDesc = textMaker.makeGameText(itemDescriber.describeWeapon(player->getActiveWeapon()));

   int startY = textSpecs.margin;
   startY = textRenderer.renderGameText(textSpecsTitle, title, startY);
   startY += textSpecsTitle.messageSpacing;

   startY = textRenderer.renderGameText(textSpecs, health, startY);
   startY += 2*textSpecs.messageSpacing;
   startY = textRenderer.renderGameText(textSpecs, strength, startY);
   startY += textSpecs.messageSpacing;
   startY = textRenderer.renderGameText(textSpecs, intelligence, startY);
   startY += 2*textSpecs.messageSpacing;
   startY = textRenderer.renderGameText(textSpecs, moveSpeed, startY);
   startY += textSpecs.messageSpacing;
   startY = textRenderer.renderGameText(textSpecs, attackSpeed, startY);

   startY += 2*textSpecs.messageSpacing;
   startY = textRenderer.renderGameText(textSpecs, weaponTitle, startY);
   startY += textSpecs.messageSpacing;
   startY = textRenderer.renderGameText(textSpecs, weaponDesc, startY);
}
