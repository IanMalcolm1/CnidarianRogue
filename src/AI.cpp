#include "Entities/AI.h"
#include <random>

/* Private Functions */

void AI::setState(AiStateId newState) {
   currentState = newState;
}

bool AI::changeState(AiStateId newState) {
   currentState = newState;
   return (currentState==newState) ? false : true;
}

AiStateId AI::rollIdleSubstate() {
    if (idleSubstates.size() == 0) {
        return AISTATE_IDLE;
    }

    srand(time(0));

    int roll = rand() % sumWeightsIdle;

    int sum = 0;
    for (AiState state : idleSubstates) {
        sum += state.weight;
        if (roll < sum) {
            return state.stateID;
        }
    }

    return AISTATE_IDLE;
}

AiStateId AI::rollAttackingSubstate() {
    if (attackingSubstates.size() == 0) {
        return AISTATE_ATTACKING;
    }

    srand(time(0));

    int roll = rand() % sumWeightsAttacking;

    int sum = 0;
    for (AiState state : attackingSubstates) {
        sum += state.weight;
        if (roll < sum) {
            return state.stateID;
        }
    }

    return AISTATE_ATTACKING;
}



/* Public Functions */

std::pair<bool, AiStateId> AI::getState() {
   bool stateChanged;
   switch (currentState) {
      case AISTATE_IDLE:
         stateChanged = changeState(rollIdleSubstate());
         break;
      case AISTATE_ATTACKING:
         stateChanged = changeState(rollAttackingSubstate());
         break;
      default:
         //substate functions should change state directly, not via this function
         return {false, currentState};
   }
}

void AI::addIdleSubstate(AiState substate) {
    removeIdleSubstate(substate.stateID);
    sumWeightsIdle += substate.weight;
    idleSubstates.push_back(substate);
}

void AI::removeIdleSubstate(AiStateId stateID) {
    for (auto iterator = idleSubstates.begin(); iterator < idleSubstates.end(); iterator++) {
        if (iterator->stateID == stateID) {
            sumWeightsIdle -= iterator->weight;
            idleSubstates.erase(iterator);
        }
    }
}

void AI::addAttackingSubstate(AiState substate) {
    removeAttackingSubstate(substate.stateID);
    sumWeightsAttacking += substate.weight;
    attackingSubstates.push_back(substate);
}

void AI::removeAttackingSubstate(AiStateId stateID) {
    for (auto iterator = attackingSubstates.begin(); iterator < attackingSubstates.end(); iterator++) {
        if (iterator->stateID == stateID) {
            sumWeightsAttacking -= iterator->weight;
            attackingSubstates.erase(iterator);
        }
    }
}
