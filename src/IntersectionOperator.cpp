// Libraries
#include <algorithm>
#include <iostream>
// Headers
#include "../headers/IntersectionOperator.h"

IntersectionOperator::IntersectionOperator() {
    std::random_device rd;
    rng.seed(rd());
}

int IntersectionOperator::decide(const std::vector<int>& state, const std::vector<int>& availableActions) {
    if (availableActions.empty()) return -1;

    std::uniform_real_distribution<double> dist(0.0, 1.0);
    if (dist(rng) < epsilon) {
        // Explore: choose random action
        std::uniform_int_distribution<size_t> actionDist(0, availableActions.size() - 1);
        return availableActions[actionDist(rng)];
    }
    // Exploit: choose best action
    if (qTable.find(state) == qTable.end()) {
        // state not in Q-table? → treat Q=0 for all → pick random action
        std::uniform_int_distribution<size_t> actionDist(0, availableActions.size() - 1);
        return availableActions[actionDist(rng)];
    }

    int bestAction = availableActions[0];
    double maxQ = -1e9; // Initialize with a very low value
    auto& actionQValues = qTable[state];
    for (int action : availableActions) {
        double q = 0.0;
        if (actionQValues.count(action)) {
            q = actionQValues[action];
        }
        if (q > maxQ) {
            maxQ = q;
            bestAction = action;
        }
    }
    return bestAction;
}

void IntersectionOperator::learn(const std::vector<int>& state, int action, double reward, const std::vector<int>& nextState, const std::vector<int>& availableActions) {
    // Q(s, a) = Q(s, a) + alpha * (reward + gamma * max_a' Q(s', a') - Q(s, a))

    double currentQ = 0.0;
    if (qTable[state].count(action)) {
        currentQ = qTable[state][action];
    }

    double maxNextQ = 0.0; // Default to 0 if next state is terminal or unknown
    if (!availableActions.empty()) {
        // Find max Q for next state
        if (qTable.count(nextState)) {
             auto& nextActionQValues = qTable[nextState];
             double localMax = -1e9;
             bool found = false;
             for (int nextAction : availableActions) {
                 double q = 0.0;
                 if (nextActionQValues.count(nextAction)) {
                     q = nextActionQValues[nextAction];
                 }
                 if (q > localMax) {
                     localMax = q;
                     found = true;
                 }
             }
             if (found) maxNextQ = localMax;
        }
    }

    double newQ = currentQ + alpha * (reward + gamma * maxNextQ - currentQ);
    qTable[state][action] = newQ;
}
