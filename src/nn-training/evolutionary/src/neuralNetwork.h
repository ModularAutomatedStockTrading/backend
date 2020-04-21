#ifndef NEURALNETWORK_H_INCLUDED
#define NEURALNETWORK_H_INCLUDED

class NeuralNetwork {
public:
    NeuralNetwork(std::vector<std::vector<std::vector<int>>> model);
    std::vector<std::vector<std::vector<int>>> get_NN();
    std::vector<int> predict(std::vector<int> input);
    void modifyWeights(double lower, double upper);
private:
    std::vector<std::vector<std::vector<int>>> NN;
};

#endif // NEURALNETWORK_H_INCLUDED
