#pragma once



struct ActorStatBlock {
	int health, maxHealth;

	int strength, dexterity, toughness;
	int wisdom, intelligence, willpower;

	int baseMoveSpeed, baseAttackSpeed;

	ActorStatBlock(int health = 0, int maxHealth = 0, int strength = 0, int dexterity = 0,
		int toughness = 0, int wisdom = 0, int intelligence = 0, int willpower = 0,
		int baseMoveSpeed = FULL_TURN_TIME, int baseAttackSpeed = FULL_TURN_TIME) :
		health(health), maxHealth(maxHealth), strength(strength), dexterity(dexterity),
		toughness(toughness), wisdom(wisdom), intelligence(intelligence),
		willpower(willpower), baseMoveSpeed(baseMoveSpeed), baseAttackSpeed(baseAttackSpeed) {};
};
