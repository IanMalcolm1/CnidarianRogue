#include "GameObjects/AI.h"
#include <random>

/* Private Functions */

AIStateID AI::rollIdleSubstate() {
    if (idleSubstates.size() == 0) {
        return AISTATE_IDLE;
    }

    srand(time(0));

    int roll = rand() % sumWeightsIdle;

    int sum = 0;
    for (AIState state : idleSubstates) {
        sum += state.weight;
        if (roll < sum) {
            return state.stateID;
        }
    }

    return AISTATE_IDLE;
}

AIStateID AI::rollAttackingSubstate() {
    if (attackingSubstates.size() == 0) {
        return AISTATE_ATTACKING;
    }

    srand(time(0));

    int roll = rand() % sumWeightsAttacking;

    int sum = 0;
    for (AIState state : attackingSubstates) {
        sum += state.weight;
        if (roll < sum) {
            return state.stateID;
        }
    }

    return AISTATE_ATTACKING;
}



/* Public Functions */

AIStateID AI::getState(AIStateID currentState) {
    switch (currentState) {
    case AISTATE_IDLE:
        currentState = rollIdleSubstate();
        break;
    case AISTATE_ATTACKING:
        currentState = rollAttackingSubstate();
        break;
    default:
        return currentState;
    }

    return currentState;
}

void AI::addIdleSubstate(AIState substate) {
    removeIdleSubstate(substate.stateID);
    sumWeightsIdle += substate.weight;
    idleSubstates.push_back(substate);
}

void AI::removeIdleSubstate(AIStateID stateID) {
    for (auto iterator = idleSubstates.begin(); iterator < idleSubstates.end(); iterator++) {
        if (iterator->stateID = stateID) {
            sumWeightsIdle -= iterator->weight;
            idleSubstates.erase(iterator);
        }
    }
}

void AI::addAttackingSubstate(AIState substate) {
    removeAttackingSubstate(substate.stateID);
    sumWeightsAttacking += substate.weight;
    attackingSubstates.push_back(substate);
}

void AI::removeAttackingSubstate(AIStateID stateID) {
    for (auto iterator = attackingSubstates.begin(); iterator < attackingSubstates.end(); iterator++) {
        if (iterator->stateID = stateID) {
            sumWeightsAttacking -= iterator->weight;
            attackingSubstates.erase(iterator);
        }
    }
}
