#ifndef MODELTRAINER_H_INCLUDED
#define MODELTRAINER_H_INCLUDED

#include <vector>
#include "neuralNetwork.h"

class ModelTrainer {
public:
    ModelTrainer(int layer_cnt, int* model, std::vector<std::vector<int>>& input, std::vector<std::vector<int>>& output);
    int getInputSize();
    void generateRandomGeneration();
    void generateMutatedGeneration(int id);
    NeuralNetwork generateMutatedInstance(NeuralNetwork instance);
    int evaluateInstance(int id);
    int getBestInstanceFromGeneration();
    void train();
private:
    std::vector<std::vector<int>> training_data_input;
    std::vector<std::vector<int>> training_data_output;
    std::vector<NeuralNetwork> neuralNetworks;
    NeuralNetwork model;
    pair<double, double> modifyRange;
};

#endif // MODELTRAINER_H_INCLUDED
