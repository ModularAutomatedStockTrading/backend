#include "modelTrainer.h"

ModelTrainer::ModelTrainer(int layer_cnt, int* model, std::vector<std::vector<int>>& input, std::vector<std::vector<int>>& output) {
    training_data_input = input;
    training_data_output = output;
}

void ModelTrainer::generateRandomGeneration() {
    for (int i = 0; i < neuralNetworks.size(); i++) {
        neuralNetworks[i] = model.generateRandomInstance();
    }
    return;
}

void ModelTrainer::generateMutatedGeneration(int id) {
    NeuralNetwork best = neuralNetworks[id];
    for (int i = 0; i < neuralNetworks.size(); i++) {
        neuralNetworks[i] = ModelTrainer::generateMutatedInstance(best);
    }
    return;
}

NeuralNetwork ModelTrainer::generateMutatedInstance(NeuralNetwork instance) {
    instance.modifyWeights(modifyRange.first, modifyRange.second);
    return instance;
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
    neuralNetworks.resize(instancesPerGeneration);
    generateRandomGeneration();
    int best;
    for (int i = 0; i < numberOfGenerations; i++) {
        best = getBestInstanceFromGeneration();
        generateMutatedGeneration(best);
    }
    return best;
}

int ModelTrainer::getInputSize() {
    return ModelTrainer::training_data_input.size();
}
