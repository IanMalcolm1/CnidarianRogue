#ifndef AI_H
#define AI_H

#include "Algorithms/Randomizer.h"
#include <vector>

/* An AI consists of a set of AiStateIds that correspond
 * to logic functions contained in the ActorManager class.
 * Different states are given different weights that
 * determine the likelihood they will be chosen. States
 * may either be chosen off of a superstate or by
 * direct modification from a logic function.
 */

enum AiStateId {
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

struct AiState {
	AiStateId stateID;
	int weight;

	AiState(AiStateId stateID, int weight = 10) : stateID(stateID), weight(weight) {};
};

class AI {
private:
	AiStateId currentState;
   bool stateChanged;

   Randomizer randomizer;

	std::vector<AiState> idleSubstates;
	int sumWeightsIdle;

	std::vector<AiState> attackingSubstates;
	int sumWeightsAttacking;

   //Returns whether the state actually changed
	AiStateId rollIdleSubstate();
	AiStateId rollAttackingSubstate();
	
public:
	AI() : currentState(AISTATE_IDLE), stateChanged(false),
   sumWeightsIdle(0), sumWeightsAttacking(0) {};

   //Returns bool to indicate whether the state changed
	std::pair<bool, AiStateId> getState();
   //Returns whether state changed
   bool changeStateTo(AiStateId newState);

	void addIdleSubstate(AiState substate);
	void removeIdleSubstate(AiStateId stateID);
	void addAttackingSubstate(AiState substate);
	void removeAttackingSubstate(AiStateId stateID);
};


#endif
