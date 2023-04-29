#include "Interface/UIScreens/PlayerUI.h"
#include "Adventure/PlayerManager.h"

void PlayerUI::initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	this->renderer = renderer;
	this->spritesheet = spritesheet;

   textRenderer.initialize(renderer, spritesheet);
}

void PlayerUI::render(const SDL_Rect& viewport) {
   ActorEntity* player = playerMan->getPlayer();
   GameText health = textMaker.makeGameText(player->stats.getHealthAsString());
   GameText strength = textMaker.makeGameText(player->stats.getStrengthAsString());
   GameText intelligence = textMaker.makeGameText(player->stats.getIntelligenceAsString());
   GameText moveSpeed = textMaker.makeGameText(player->stats.getMoveSpeedAsString());
   GameText attackSpeed = textMaker.makeGameText(player->stats.getAttackSpeedAsString());

   textSpecs.setViewportWidth(viewport.w);

   int startY = textSpecs.margin;
   startY = textRenderer.renderGameText(textSpecs, health, startY);
   startY += textSpecs.fontSizePixels;
   startY = textRenderer.renderGameText(textSpecs, strength, startY);
   startY += textSpecs.fontSizePixels;
   startY = textRenderer.renderGameText(textSpecs, intelligence, startY);
   startY += textSpecs.fontSizePixels;
   startY = textRenderer.renderGameText(textSpecs, moveSpeed, startY);
   startY += textSpecs.fontSizePixels;
   startY = textRenderer.renderGameText(textSpecs, attackSpeed, startY);
}
