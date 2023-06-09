#ifndef AI_H
#define AI_H


enum AiType {
   AITYPE_MELEE,
   AITYPE_RANGED,
};

enum AiState {
	//Idle and substates
	AISTATE_IDLE,
	AISTATE_SLEEPING,
	AISTATE_WANDERING,

	//Attacking and substates
	AISTATE_ATTACKING,
	AISTATE_FLEEING,
   AISTATE_APPROACH_AND_WHACK,


	//Total number of AI states
	AISTATE_TOTAL_STATES
};

#endif
