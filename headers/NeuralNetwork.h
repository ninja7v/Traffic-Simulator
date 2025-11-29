/**
 * @brief Implementation of a neural network (more precisely a MultiLayer Perceptron - MLP) to approximate Q-values.
 */

#pragma once
#include <vector>
#include <cmath>
#include <random>
#include <iostream>
#include <fstream>

struct Layer {
    int inputSize;
    int outputSize;
    std::vector<std::vector<double>> weights;
    std::vector<double> biases;
    std::vector<double> inputs;
    std::vector<double> z_values; // Pre-activation
    std::vector<double> activations; // Post-activation

    Layer(int in, int out);
};

class NeuralNetwork {
public:
    NeuralNetwork();
    NeuralNetwork(const std::vector<int>& topology, double learningRate = 0.01);

    void init(const std::vector<int>& topology, double learningRate = 0.01);
    std::vector<double> predict(const std::vector<double>& input);
    void train(const std::vector<double>& input, const std::vector<double>& target);

private:
    std::vector<Layer> layers;
    double learningRate;

    // Activation functions
    double sigmoid(double x);
    double sigmoidDerivative(double x);
    double relu(double x);
    double reluDerivative(double x);
};
