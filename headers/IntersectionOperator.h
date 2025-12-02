/**
 * @brief Abstract base class for intersection control operators.
 */

#pragma once
// Libraries
#include <vector>

class IntersectionOperator {
public:
    virtual ~IntersectionOperator() = default;

    /**
     * @brief Decide which road should have the green light.
     * @param state The current state vector.
     * @param availableActions List of valid road indices that can be green.
     * @return The index of the road to turn green.
     */
    virtual int decide(const std::vector<int>& state, const std::vector<int>& availableActions) = 0;

    /**
     * @brief Update the agent based on the transition.
     * @param state Previous state.
     * @param action Action taken (road index).
     * @param reward Reward received.
     * @param nextState Current state.
     * @param availableActions Actions available in the next state.
     */
    virtual void learn(const std::vector<int>& state, const int action, const double reward, const std::vector<int>& nextState, const std::vector<int>& availableActions) = 0;
};
