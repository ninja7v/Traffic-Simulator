#pragma once
#include "IntersectionOperator.h"
#include "NeuralNetwork.h"
#include <random>

/**
 * @brief Deep Reinforcement Learning Operator (DQN Agent).
 * 
 * This operator uses a Neural Network to approximate the Q-values of the traffic light phases.
 * It learns to minimize waiting time by interacting with the environment.
 */
class DeepRLOperator : public IntersectionOperator {
public:
    DeepRLOperator();
    int decide(const std::vector<int>& state, const std::vector<int>& availableActions) override;
    void learn(const std::vector<int>& state, int action, double reward, const std::vector<int>& nextState, const std::vector<int>& availableActions) override;

private:
    NeuralNetwork policyNetwork;
    bool isInitialized = false;

    // Structure to store a single transition (experience)
    struct Experience {
        std::vector<double> state;      // Current traffic state
        int action;                     // Traffic light phase chosen
        double reward;                  // Reward received (negative waiting time)
        std::vector<double> nextState;  // Resulting state
        bool done;                      // Is the episode finished? (Not used here but standard in RL)
    };

    std::vector<Experience> replayBuffer; // Memory to store past experiences
    const size_t maxBufferSize = 10000;   // Maximum number of experiences to keep
    const size_t batchSize = 32;          // Number of experiences to train on at each step
    const int trainingFrequency = 1;      // Train the network every N steps
    int stepCount = 0;

    // Hyperparameters
    double alpha = 0.001;       // Learning Rate: How fast the network updates its weights
    double gamma = 0.95;        // Discount Factor: Importance of future rewards (0 = short-sighted, 1 = long-sighted)
    double epsilon = 1.0;       // Exploration Rate: Probability of choosing a random action
    double epsilonMin = 0.01;   // Minimum Exploration Rate: The agent will always explore a little bit
    double epsilonDecay = 0.995;// Decay Rate: How fast epsilon decreases (multiplied at each step)

    std::mt19937 rng;
};
