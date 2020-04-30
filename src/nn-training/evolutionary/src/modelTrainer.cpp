#include "modelTrainer.h"
#include <stdlib.h>
#include <iostream>
#include <cfloat>

//#define DEBUG

#define print(val) std::cout << val << std::endl;
#define printNoEndl(val) std::cout << val;
#define printVector(vec) for(auto el : vec) std::cout << el << " "; std::cout << std::endl; 

ModelTrainer::ModelTrainer(
    std::vector<int>& model,
    std::vector<std::vector<double>>& input,
    std::vector<std::vector<double>>& output,
    bool withBias
) {
    training_data_input = input;
    training_data_output = output;
    modelTemplate = model;
    this->withBias = withBias;
}

void ModelTrainer::generateRandomGeneration() {
    /*
    Generate random instances in neuralNetworks vector
    Input   -> void
    Output  -> void
    */
    for (int i = 0; (unsigned)i < neuralNetworks.size(); i++) {
        neuralNetworks[i].generateRandomInstance(modelTemplate);
    }
}

void ModelTrainer::generateMutatedGeneration(int id) {
    for (int i = 0; (unsigned)i < neuralNetworks.size(); i++) {
        if(i != id){
            neuralNetworks[i] = neuralNetworks[id];
            neuralNetworks[i].modifyWeights(mutationRange);
        }
    }
}

void ModelTrainer::printModel(int id){
    std::vector<std::vector<std::vector<double>>> model;
    neuralNetworks[id].get_NN(model);
    std::cout << "   start model " << id << std::endl; 
    for(auto el1 : model){
        for(auto el2 : el1){
            for(auto el3 : el2){
                printNoEndl("   ");std::cout << el3 << std::endl;
            }
        }
    }
    std::cout << "   end model " << id << std::endl; 
}

double ModelTrainer::evaluateInstance(int id) {
    double sum = 0;
    for (int i = 0; (unsigned)i < training_data_input.size(); i++) {
        std::vector<double> output;
        //printModel(id);
        neuralNetworks[id].predict(training_data_input[i], output);
        #ifdef DEBUG
        print(id);
        print("   input");
        printNoEndl("   "); printVector(training_data_input[i]);
        print("   output");
        printNoEndl("   "); printVector(output);
        #endif
        for(int j = 0; (unsigned)j < output.size(); j++){
            sum += abs(output[j] - training_data_output[i][j]);
        }
    }
    return sum / training_data_input.size();
}

//[[1,1],[0,1], [1,0]]
//[[0.5684, 0.866],[0.5684, 0.866],[0.5684, 0.866]]

int ModelTrainer::getBestInstanceFromGeneration() {
    int best = -1;
    double bestPerformance = DBL_MAX;
    for (int i = 0; (unsigned)i < neuralNetworks.size(); i++) {
        double performance = evaluateInstance(i);
        if (performance < bestPerformance) {
            best = i;
            bestPerformance = performance;
        }
    }
    #ifndef DEBUG
    std::cout << "best performance: " << bestPerformance << std::endl;
    #endif
    return best;
}

int ModelTrainer::train(double mutationRange, int numberOfGenerations, int instancesPerGeneration) {
    srand(time(NULL)); // bad
    this->mutationRange = mutationRange;
    neuralNetworks = std::vector<NeuralNetwork>(instancesPerGeneration, NeuralNetwork(withBias));
    generateRandomGeneration();
    int best = -1;
    for (int i = 0; i < numberOfGenerations; i++) {
        #ifndef DEBUG
        std::cout << "generation: " << i + 1 << std::endl;
        #endif
        best = getBestInstanceFromGeneration();
        generateMutatedGeneration(best);
    }
    #ifdef DEBUG
    print("training ended");
    for(int i = 0; (unsigned)i < training_data_input.size(); i++){
        std::vector<double> output;
        neuralNetworks[best].predict(training_data_input[i], output);
        print("   input");
        printNoEndl("   "); printVector(training_data_input[i]);
        print("   output");
        printNoEndl("   "); printVector(output);
    }
    #endif
    return best;
}

void ModelTrainer::get_model(int id, std::vector<std::vector<std::vector<double>>>& NN) {
    neuralNetworks[id].get_NN(NN);
}
