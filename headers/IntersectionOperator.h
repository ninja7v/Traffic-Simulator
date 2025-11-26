/**
 * @brief Define intersection operator, a class that implements RL methods to control traffic lights.
 */

#pragma once
// Libraries
#include <vector>
#include <map>
#include <random>

class IntersectionOperator {
public:
    IntersectionOperator();

    /**
     * @brief Decide which road should have the green light.
     * @param state The current state vector.
     * @param availableActions List of valid road indices that can be green.
     * @return The index of the road to turn green.
     */
    int decide(const std::vector<int>& state, const std::vector<int>& availableActions);

    /**
     * @brief Update the Q-table based on the transition.
     * @param state Previous state.
     * @param action Action taken (road index).
     * @param reward Reward received.
     * @param nextState Current state.
     * @param availableActions Actions available in the next state.
     */
    void learn(const std::vector<int>& state, int action, double reward, const std::vector<int>& nextState, const std::vector<int>& availableActions);

private:
    // Q-Table: Map state vector to a map of Action -> Q-Value
    // We use a map because the state space is sparse and potentially large.
    std::map<std::vector<int>, std::map<int, double>> qTable;

    // Hyperparameters
    double alpha = 0.1;   // Learning rate
    double gamma = 0.9;   // Discount factor
    double epsilon = 0.1; // Exploration rate

    std::mt19937 rng;
};
