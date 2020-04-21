#ifndef MODELTRAINER_H_INCLUDED
#define MODELTRAINER_H_INCLUDED

#include <vector>
#include "neuralNetwork.h"

class ModelTrainer {
public:
    ModelTrainer(int layer_cnt, int* model, std::vector<std::vector<int>>& input, std::vector<std::vector<int>>& output);
    void generateRandomGeneration();
    void generateRandomInstance(int id);
    void generateMutatedGeneration(int id);
    void generateMutatedInstance(NeuralNetwork instance, int id);
    int evaluateInstance(int id);
    int getBestInstanceFromGeneration();
    int train(std::pair<double, double> mutationRate, int numberOfGenerations, int instancesPerGeneration);
    std::vector<std::vector<std::vector<int>>> get_model(int id);
private:
    std::vector<std::vector<int>> training_data_input;
    std::vector<std::vector<int>> training_data_output;
    std::vector<NeuralNetwork> neuralNetworks;
    std::pair<double, double> modifyRange;
    vector<int> modelTemplate;
};

#endif // MODELTRAINER_H_INCLUDED
