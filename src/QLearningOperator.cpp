#include "../headers/QLearningOperator.h"
#include <iostream>

QLearningOperator::QLearningOperator() {
    std::random_device rd;
    rng.seed(rd());
}

int QLearningOperator::decide(const std::vector<int>& state, const std::vector<int>& availableActions) {
    if (availableActions.empty()) return -1;

    std::uniform_real_distribution<double> dist(0.0, 1.0);
    if (dist(rng) < epsilon) {
        std::uniform_int_distribution<size_t> actionDist(0, availableActions.size() - 1);
        return availableActions[actionDist(rng)];
    }

    if (qTable.find(state) == qTable.end()) {
        std::uniform_int_distribution<size_t> actionDist(0, availableActions.size() - 1);
        return availableActions[actionDist(rng)];
    }

    int bestAction = availableActions[0];
    double maxQ = -1e9;
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

void QLearningOperator::learn(const std::vector<int>& state, int action, double reward, const std::vector<int>& nextState, const std::vector<int>& availableActions) {
    double currentQ = 0.0;
    if (qTable[state].count(action)) {
        currentQ = qTable[state][action];
    }

    double maxNextQ = 0.0;
    if (!availableActions.empty()) {
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
