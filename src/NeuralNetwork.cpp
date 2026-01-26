// Libraries
#include <cmath>    // To use std::sqrt and std::exp
#include <cstdlib>  // To use rand()
#include <ctime>    // To use time()
// Headers
#include "../headers/NeuralNetwork.h"

Layer::Layer(const int in, const int out) : inputSize(in), outputSize(out) {
    // Xavier or He initialization methods could be better, but simple random is fine for now
    const double scale = sqrt(2.0 / static_cast<double>(in));
    for (int i = 0; i < out; ++i) {
        std::vector<double> row;
        for (int j = 0; j < in; ++j) {
            // Random value between -1 and 1 scaled
            double const r = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
            row.push_back(r * scale);
        }
        weights.push_back(row);
        biases.push_back(0.0);
    }
}

NeuralNetwork::NeuralNetwork() : learningRate(0.01) {}

NeuralNetwork::NeuralNetwork(const std::vector<int>& topology, double lr) : learningRate(lr) {
    layers.clear();
    for (size_t i = 0; i < topology.size() - 1; ++i) {
        layers.emplace_back(topology[i], topology[i + 1]);
    }
}

// double NeuralNetwork::sigmoid(const double x) {
//     return 1.0 / (1.0 + exp(-x));
// }

// double NeuralNetwork::sigmoidDerivative(const double x) {
//     double s = sigmoid(x);
//     return s * (1.0 - s);
// }

double NeuralNetwork::relu(const double x) {
    return x > 0 ? x : 0.01 * x; // Leaky ReLU to avoid dead neurons
}

double NeuralNetwork::reluDerivative(const double x) {
    return x > 0 ? 1.0 : 0.01;
}

std::vector<double> NeuralNetwork::predict(const std::vector<double>& input) {
    std::vector<double> currentInput = input;

    for (size_t i = 0; i < layers.size(); ++i) {
        Layer& layer = layers[i];
        layer.inputs = currentInput;
        layer.z_values.clear();
        layer.activations.clear();

        std::vector<double> nextInput;
        for (int n = 0; n < layer.outputSize; ++n) {
            double sum = layer.biases[n];
            for (int w = 0; w < layer.inputSize; ++w) {
                sum += layer.weights[n][w] * currentInput[w];
            }
            layer.z_values.push_back(sum);
            
            // Activation
            const double val = i == layers.size() - 1 ?
                sum /* Output Layer */ : relu(sum) /* Hidden Layer */; 
            layer.activations.push_back(val);
            nextInput.push_back(val);
        }
        currentInput = nextInput;
    }
    return currentInput;
}

void NeuralNetwork::train(const std::vector<double>& input, const std::vector<double>& target) {
    // Forward pass to populate activations
    std::vector<double> output = predict(input);

    // Backward pass
    std::vector<double> errors;
    
    // Calculate output error (MSE derivative: output - target)
    for (size_t i = 0; i < output.size(); ++i) {
        errors.push_back(output[i] - target[i]);
    }

    // Backpropagate
    for (int i = static_cast<int>(layers.size()) - 1; i >= 0; --i) {
        Layer& layer = layers[i];
        std::vector<double> nextErrors(layer.inputSize, 0.0);

        for (int n = 0; n < layer.outputSize; ++n) {         
            const double derivative = (i == layers.size() - 1) ? 1.0 : reluDerivative(layer.z_values[n]); 
            const double delta = errors[n] * derivative;

            // Update weights and biases
            for (int w = 0; w < layer.inputSize; ++w) {
                // Gradient w.r.t weight is delta * input
                const double inputVal = layer.inputs[w];
                // Accumulate error for previous layer
                nextErrors[w] += delta * layer.weights[n][w];
                
                // Update weight
                layer.weights[n][w] -= learningRate * delta * inputVal;
            }
            // Update bias
            layer.biases[n] -= learningRate * delta;
        }
        errors = nextErrors;
    }
}
