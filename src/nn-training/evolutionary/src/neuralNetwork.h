#ifndef NEURALNETWORK_H_INCLUDED
#define NEURALNETWORK_H_INCLUDED

#include <vector>

class NeuralNetwork {
public:
    NeuralNetwork(bool withBias);
    void get_NN(std::vector<std::vector<std::vector<double>>>& NN);
    void generateRandomInstance(std::vector<int>& modelTemplate);
    std::vector<double> matrixMultiplication(
        std::vector<double>& a,
        std::vector<std::vector<double>> b
    );
    void predict(std::vector<double>& input, std::vector<double>& output);
    void modifyWeights(double mutationRange);
private:
    std::vector<std::vector<std::vector<double>>> NN;
    bool withBias;
};

#endif // NEURALNETWORK_H_INCLUDED
