#ifndef AI_H
#define AI_H

#include <vector>

/* An AI consists of a set of AiStateIds that correspond
 * to logic functions contained in the ActorManager class.
 * Different states are given different weights that
 * determine the likelihood they will be chosen. States
 * may either be chosen off of a superstate or by
 * direct modification from a logic function.
 */

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

   //Returns whether the state actually changed
   bool changeState(AiStateId newState);
	AiStateId rollIdleSubstate();
	AiStateId rollAttackingSubstate();
	
public:
	AI() : currentState(AISTATE_IDLE), stateChanged(false),
   sumWeightsIdle(0), sumWeightsAttacking(0) {};

   //Returns bool to indicate whether the state changed
	std::pair<bool, AiStateId> getState();
   void setState(AiStateId newState);

	void addIdleSubstate(AiState substate);
	void removeIdleSubstate(AiStateId stateID);
	void addAttackingSubstate(AiState substate);
	void removeAttackingSubstate(AiStateId stateID);
};


#endif
