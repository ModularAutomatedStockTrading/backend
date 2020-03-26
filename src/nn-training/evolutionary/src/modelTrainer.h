#ifndef MODELTRAINER_H_INCLUDED
#define MODELTRAINER_H_INCLUDED

#include <vector>
#include "neuralNetwork.h"

class ModelTrainer {
public:
    ModelTrainer(int layer_cnt, int* model, std::vector<std::vector<int>>& input, std::vector<std::vector<int>>& output);
    int getInputSize();
private:
    std::vector<std::vector<int>> training_data_input;
    std::vector<std::vector<int>> training_data_output;
    std::vector<NeuralNetwork> neuralNetworks;
    NeuralNetwork model;
};

#endif // MODELTRAINER_H_INCLUDED

/*
class ModelTrainer{
    constructor(training_data, info_om_model)
        // call generateRandomGeneration()

    generateRandomGeneration()
        // fills neuralNetworks with instances

    evaluateInstance(NeuralNetwork nn, startIdx, endIdx)
        // take one NN and return heuristic (how good was it)
        int cnt = 0;
        for datapoint in data:
            // datapoint {
                inputs : []
                outputs : []
            }
            output = nn.predict(datapoint.input)
            cnt += (output == datapoint.output)
        return cnt
        @return Number

    getBestInstanceFromGeneration(startIdx, endIdx)
        // evaluateInstance for all NN and find the best
        best  = null
        bestPerformance = -1
        for NN in neuralNetworks:
            int performance = evaluateInstance(NN)
            if(performance > bestPerformance){
                best =  NN
                bestPerformance = performance
            }
        return best
        @return NeuralNetwork

    generatedMutatedGeneration(NeuralNetwork best)
        // fills neuralNetworks with mutations of best

    train(metadata)
        metadata : {
            // mutation rate
            // # of generations
            // # instances per generation
        }
        NeuralNetwork best
        for i op til number of generations:
            best = getBestInstanceFromGeneration()
            generatedMutatedGeneration(best)
        return best
        // return best instance
}

class NeuralNetwork(){
    //magic
}
*/
