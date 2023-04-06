#ifndef AI_H
#define AI_H

#include <vector>

enum AiStateId {
	//Superstates and defaults, used to branch into substates

	AISTATE_IDLE,
	AISTATE_ATTACKING,

	//Idle substates

	AISTATE_SLEEPING,
	AISTATE_WANDERING,


	//Attacking substates

	AISTATE_FLEEING,


	//Total number of AI states
	AISTATE_TOTAL_STATES
};

struct AiState {
	AiStateId stateID;
	int weight;

	AiState(AiStateId stateID, int weight = 10) : stateID(stateID), weight(weight) {};
};

class AI {
private:
	AiStateId currentState;
   bool stateChanged;

	std::vector<AiState> idleSubstates;
	int sumWeightsIdle;

	std::vector<AiState> attackingSubstates;
	int sumWeightsAttacking;

   bool changeState(AiStateId newState);
	AiStateId rollIdleSubstate();
	AiStateId rollAttackingSubstate();
	
public:
	AI() : currentState(AISTATE_IDLE), stateChanged(false),
   sumWeightsIdle(0), sumWeightsAttacking(0) {};

   //returns bool to indicate whether the state changed
	std::pair<bool, AiStateId> getState();
   void setState(AiStateId newState);

	void addIdleSubstate(AiState substate);
	void removeIdleSubstate(AiStateId stateID);
	void addAttackingSubstate(AiState substate);
	void removeAttackingSubstate(AiStateId stateID);
};


#endif
