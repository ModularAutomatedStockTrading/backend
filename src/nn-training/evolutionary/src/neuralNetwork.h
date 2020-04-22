#ifndef NEURALNETWORK_H_INCLUDED
#define NEURALNETWORK_H_INCLUDED

#include <vector>

class NeuralNetwork {
public:
    NeuralNetwork(std::vector<std::vector<std::vector<double>>> model);
    std::vector<std::vector<std::vector<double>>> get_NN();
    void set_NN(std::vector<std::vector<std::vector<double>>> NN);
    std::vector<int> predict(std::vector<int> input);
    void modifyWeights(double lower, double upper);
private:
    std::vector<std::vector<std::vector<double>>> NN;
};

#endif // NEURALNETWORK_H_INCLUDED
