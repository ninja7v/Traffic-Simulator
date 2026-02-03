#pragma once
// Libraries
#include <map>    // To use std::map
#include <vector> // To use std::vector
#include <random> // To use std::mt19937
// Headers
#include "IntersectionOperator.h"

class QLearningOperator : public IntersectionOperator {
public:
  /** @brief Default constructor. */
    QLearningOperator();
  /** @brief Decide the next action to take.
    * @param state Current state of the environment.
    * @param availableActions List of available actions.
    * @return int Chosen action. */
    int decide(const std::vector<int>& state,
               const std::vector<int>& availableActions) override;
  /** @brief Learn from the environment.
    * @param state Current state of the environment.
    * @param action Chosen action.
    * @param reward Reward received.
    * @param nextState Resulting state.
    * @param availableActions List of available actions. */
    void learn(const std::vector<int>& state,
               const int action,
               const double reward,
               const std::vector<int>& nextState,
               const std::vector<int>& availableActions) override;

private:
    /** Q-Table containing the expected future reward (Q-value) for each action in every state */
    std::map<std::vector<int>, std::map<int, double>> qTable;
  
/** @defgroup hyperparameters */
/**@{*/
    /** Learning Rate: How fast the network updates its weights */
    static constexpr inline double alpha = 0.001;
    /** Discount Factor: Importance of future rewards (0 = short-sighted, 1 = long-sighted) */
    static constexpr inline double gamma = 0.95;
    /** Exploration Rate: Probability of choosing a random action */
    static constexpr inline double epsilon = 0.1; // 10% exploration
    /** Random number generator */
    std::mt19937 rng;
/**@}*/
};
