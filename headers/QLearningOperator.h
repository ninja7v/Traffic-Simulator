#pragma once
#include "IntersectionOperator.h"
#include <map>
#include <random>

class QLearningOperator : public IntersectionOperator {
public:
    QLearningOperator();
    int decide(const std::vector<int>& state, const std::vector<int>& availableActions) override;
    void learn(const std::vector<int>& state, int action, double reward, const std::vector<int>& nextState, const std::vector<int>& availableActions) override;

private:
    std::map<std::vector<int>, std::map<int, double>> qTable;
    double alpha = 0.1;
    double gamma = 0.9;
    double epsilon = 0.1;
    std::mt19937 rng;
};
