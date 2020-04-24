#include "modelTrainer.h"
#include <stdlib.h>
#include <iostream>

ModelTrainer::ModelTrainer(std::vector<int>& model, std::vector<std::vector<double>>& input, std::vector<std::vector<double>>& output) {
    training_data_input = input;
    training_data_output = output;
    modelTemplate = model;
}

void ModelTrainer::generateRandomGeneration() {
    /*
    Generate random instances in neuralNetworks vector
    Input   -> void
    Output  -> void
    */
    for (int i = 0; i < neuralNetworks.size(); i++) {
        neuralNetworks[i].generateRandomInstance(modelTemplate);
    }
}

void ModelTrainer::generateMutatedGeneration(int id) {
    for (int i = 0; i < neuralNetworks.size(); i++) {
        neuralNetworks[i] = neuralNetworks[id];
        neuralNetworks[i].modifyWeights(mutationRange);
    }
}

int ModelTrainer::evaluateInstance(int id) {
    int cnt = 0;
    for (int i = 0; i < training_data_input.size(); i++) {
        std::vector<double> output;
        neuralNetworks[id].predict(training_data_input[i], output);
        if (output == training_data_output[i])
            cnt++;
    }
    return cnt;
}

int ModelTrainer::getBestInstanceFromGeneration() {
    int best = -1;
    int bestPerformance = -1;
    for (int i = 0; i < neuralNetworks.size(); i++) {
        int performance = evaluateInstance(i);
        std::cout << performance << std::endl;
        if (performance > bestPerformance) {
            best = i;
            bestPerformance = performance;
        }
    }
    return best;
}

int ModelTrainer::train(double mutationRange, int numberOfGenerations, int instancesPerGeneration) {
    srand(time(NULL)); // bad
    this->mutationRange = mutationRange;
    neuralNetworks = std::vector<NeuralNetwork>(instancesPerGeneration, NeuralNetwork());
    generateRandomGeneration();
    int best;
    for (int i = 0; i < numberOfGenerations; i++) {
        best = getBestInstanceFromGeneration();
        generateMutatedGeneration(best);
    }
    return best;
}

void ModelTrainer::get_model(int id, std::vector<std::vector<std::vector<double>>>& NN) {
    neuralNetworks[id].get_NN(NN);
}
