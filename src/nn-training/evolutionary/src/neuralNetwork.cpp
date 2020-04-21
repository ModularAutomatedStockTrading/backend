#include "neuralNetwork.h"

NeuralNetwork::NeuralNetwork(std::vector<std::vector<std::vector<int>>> model) {
    NN = model;
}

std::vector<std::vector<std::vector<int>>> NeuralNetwork::get_NN() {
    return NN;
}

std::vector<int> NeuralNetwork::predict(std::vector<int> input) {
    return input;
}

void NeuralNetwork::modifyWeights(double lower, double upper) {
    return;
}
