/**
 * @brief Implementation of a neural network (more precisely a MultiLayer Perceptron - MLP) to approximate Q-values.
 */

#pragma once
// Libraries
#include <vector> // To use std::vector
#include <random>  // To use std::mt19937
#include <iostream> // To use std::cout
#include <fstream> // To use std::ofstream

/**
 * @brief Define the parameters of a layer.
 */
struct Layer {
    int inputSize;
    int outputSize;
    std::vector<std::vector<double>> weights;
    std::vector<double> biases;
    std::vector<double> inputs;
    std::vector<double> z_values; // Pre-activation
    std::vector<double> activations; // Post-activation

    Layer(const int in, const int out);
};

class NeuralNetwork {
public:
    /**
     * @brief Default constructor.
     */
    NeuralNetwork();
    /**
     * @brief Constructor.
     * @param topology Vector of integers representing the number of neurons in each layer.
     * @param learningRate Learning rate for the network.
     */
    NeuralNetwork(const std::vector<int>& topology, double learningRate = 0.01);

    /**
     * @brief Initialize the network.
     * @param topology Vector of integers representing the number of neurons in each layer.
     * @param learningRate Learning rate for the network.
     */
    void init(const std::vector<int>& topology, double learningRate = 0.01);
    /**
     * @brief Make a prediction.
     * @param input Input vector.
     * @return std::vector<double> Output vector (size = number of layers * number of actions)
     */
    std::vector<double> predict(const std::vector<double>& input);
    /**
     * @brief Train the network.
     * @param input Input vector.
     * @param target Target vector.
     */
    void train(const std::vector<double>& input, const std::vector<double>& target);

private:
    /**
     * @brief Vector of layers.
     */
    std::vector<Layer> layers;
    /**
     * @brief Learning rate.
     */
    double learningRate;

    // /**
    //  * @brief Activation function.
    //  * @param x Input value.
    //  * @return double Output value.
    //  */
    // double sigmoid(const double x);
    // /**
    //  * @brief Derivative of the activation function.
    //  * @param x Input value.
    //  * @return double Output value.
    //  */
    // double sigmoidDerivative(const double x);
    /**
     * @brief Activation function.
     * @param x Input value.
     * @return double Output value.
     */
    double relu(const double x);
    /**
     * @brief Derivative of the activation function.
     * @param x Input value.
     * @return double Output value.
     */
    double reluDerivative(const double x);
};
