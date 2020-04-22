#include "modelTrainer.h"
#include <stdlib.h>
#include <time.h>

ModelTrainer::ModelTrainer(std::vector<int>& model, std::vector<std::vector<int>>& input, std::vector<std::vector<int>>& output) {
    training_data_input = input;
    training_data_output = output;
    modelTemplate = model;
}

void ModelTrainer::generateRandomGeneration() {
    for (int i = 0; i < neuralNetworks.size(); i++) {
        generateRandomInstance(i);
    }
}

void ModelTrainer::generateRandomInstance(int id) {
    srand(time(NULL));
    std::vector<std::vector<std::vector<double>>> NN(modelTemplate.size());
    for (int i = 0; i < modelTemplate.size() - 1; i++) {
        NN[i].resize(modelTemplate[i]);
        for (int j = 0; j < modelTemplate[i]; j++) {
            NN[i][j].resize(modelTemplate[i + 1]);
            for (int k = 0; k < modelTemplate[i + 1]; k++) {
                NN[i][j][k] = (double)rand() / RAND_MAX;
            }
        }
    }
    neuralNetworks[id].set_NN(NN);
}

void ModelTrainer::generateMutatedGeneration(int id) {
    for (int i = 0; i < neuralNetworks.size(); i++) {
        generateMutatedInstance(neuralNetworks[id], i);
    }
}

void ModelTrainer::generateMutatedInstance(NeuralNetwork instance, int id) {
    instance.modifyWeights(modifyRange.first, modifyRange.second);
    neuralNetworks[id] = instance;
}

int ModelTrainer::evaluateInstance(int id) {
    int cnt = 0;
    for (int i = 0; i < training_data_input.size(); i++) {
        std::vector<int> output = neuralNetworks[id].predict(training_data_input[i]);
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
        if (performance > bestPerformance) {
            best = i;
            bestPerformance = performance;
        }
    }
    return best;
}

int ModelTrainer::train(std::pair<double, double> mutationRate, int numberOfGenerations, int instancesPerGeneration) {
    modifyRange = mutationRate;
    neuralNetworks = std::vector<NeuralNetwork>(instancesPerGeneration, NeuralNetwork(std::vector<std::vector<std::vector<double>>>()));
    generateRandomGeneration();
    int best;
    for (int i = 0; i < numberOfGenerations; i++) {
        best = getBestInstanceFromGeneration();
        generateMutatedGeneration(best);
    }
    return best;
}

std::vector<std::vector<std::vector<double>>> ModelTrainer::get_model(int id) {
    return neuralNetworks[id].get_NN();
}
