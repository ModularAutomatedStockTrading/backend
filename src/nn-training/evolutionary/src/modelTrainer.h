#ifndef MODELTRAINER_H_INCLUDED
#define MODELTRAINER_H_INCLUDED

#include <vector>
#include <stdlib.h>
#include <time.h>
#include "neuralNetwork.h"

class ModelTrainer {
public:
    ModelTrainer(std::vector<int>& model, std::vector<std::vector<double>>& input, std::vector<std::vector<double>>& output);
    void generateRandomGeneration();
    void generateMutatedGeneration(int id);
    void generateMutatedInstance(NeuralNetwork instance, int id);
    int evaluateInstance(int id);
    int getBestInstanceFromGeneration();
    int train(double mutationRange, int numberOfGenerations, int instancesPerGeneration);
    void get_model(int id, std::vector<std::vector<std::vector<double>>>& NN);
private:
    std::vector<std::vector<double>> training_data_input;
    std::vector<std::vector<double>> training_data_output;
    std::vector<NeuralNetwork> neuralNetworks;
    double mutationRange;
    std::vector<int> modelTemplate;
};

#endif // MODELTRAINER_H_INCLUDED
