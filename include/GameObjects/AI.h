#ifndef AI_H
#define AI_H

#include <vector>

enum AIStateID {
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

struct AIState {
	AIStateID stateID;
	int weight;

	AIState(AIStateID stateID, int weight = 10) : stateID(stateID), weight(weight) {};
};

class AI {
private:
	std::vector<AIState> idleSubstates;
	int sumWeightsIdle;

	std::vector<AIState> attackingSubstates;
	int sumWeightsAttacking;

	AIStateID rollIdleSubstate();
	AIStateID rollAttackingSubstate();
	
public:
	AI() : sumWeightsIdle(0), sumWeightsAttacking(0) {};

	AIStateID getState(AIStateID currentState);

	void addIdleSubstate(AIState substate);
	void removeIdleSubstate(AIStateID stateID);
	void addAttackingSubstate(AIState substate);
	void removeAttackingSubstate(AIStateID stateID);
};


#endif
