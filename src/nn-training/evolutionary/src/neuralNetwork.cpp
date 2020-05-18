#include "neuralNetwork.h"
#include <stdlib.h>
#include <iostream>
#include "activationfunctions.cpp"
#define printVector(vec) for(auto el : vec) std::cout << el << " "; std::cout << std::endl; 

NeuralNetwork::NeuralNetwork(bool withBias) {
	/*
	Constructor function for the NeuralNetwork class.
	Input -> bool withBias
	Output -> NeuralNetwork object
	*/
    NN = std::vector<std::vector<std::vector<double>>>();
	this->withBias = withBias;
}

void NeuralNetwork::get_NN(std::vector<std::vector<std::vector<double>>>& NN) {
	/*
	Gets the 3D vector NN by changing the input 3D vector to match the 3D vector this->NN.
	Input -> vector<std::vector<std::vector<double>>>& NN
	Output -> void
	*/
    NN = this->NN;
}

void NeuralNetwork::set_NN(std::vector<std::vector<std::vector<double>>>& NN) {
	/*
	Sets the 3D vector this->NN by changing the 3D vector to match the 3D vector NN.
	Input -> vector<std::vector<std::vector<double>>>& NN
	Output -> void
	*/
    this->NN = NN;
}


std::vector<double> NeuralNetwork::matrixMultiplication(
    std::vector<double>& a,
    std::vector<std::vector<double>> b
) {
	/*
	Multiplies a matrix and a vector.
	Input -> vector<std::vector<double>> b (the matrix), vector<double>& a (the vector)
	Output -> std::vector<double> res (a vector)
	*/
    std::vector<double> res(b[0].size(), 0);
    for (int i = 0; (unsigned)i < res.size(); i++) {
        for (int j = 0; (unsigned)j < (withBias ? b.size() - 1 : b.size()); j++)
            res[i] += a[j] * b[j][i];
		if (withBias) res[i] += b[b.size() - 1][i];
	}
	return res;
}

// a[nextLayerNode] = sum of values
// b[node][nextLayerNode] = weight;

void NeuralNetwork::predict(std::vector<double>& input, std::vector<double>& output) {
	/*
	Predicts an output via the the neural network NN, changes the vector output to reflect this.
	Input -> vector<double>& input, vector<double>& output
	Output -> void
	*/
	std::vector<double> current = input;
	for (int layer = 0; (unsigned)layer < NN.size() - 1; layer++) {
		current = matrixMultiplication(current, NN[layer]);
		for (int i = 0; (unsigned)i < current.size(); i++) {
			if((unsigned) layer == NN.size() - 2) current[i] = Activation::activate(current[i], "SQNL");
			else current[i] = Activation::activate(current[i], "logistic");
		}
	}
	// printVector(current);
	output = current;
}

void NeuralNetwork::modifyWeights(double mutationRange) {
	/*
	Modifies all weights, within some range, in the neural network NN.
	Input -> double mutationRange
	Output -> void
	*/
    double range = (double)(rand() % (int)(mutationRange * 1000000)) / 1000000; 0 - 0.5;
	for (int i = 0; (unsigned)i < NN.size(); i++) {
        for (int j = 0; (unsigned)j < NN[i].size(); j++) {
            for (int k = 0; (unsigned)k < NN[i][j].size(); k++) {
				double change = (double)(rand() % (int)(range * 1000000 * 2)) / 1000000 - range;
				//std::cout << change << std::endl;
                NN[i][j][k] += change;
            }
        }
    }
}

void NeuralNetwork::generateRandomInstance(std::vector<int>& modelTemplate) {
	/*
	Resizes the 3D vector NN to match the modelTemplate 3D vector.
	Sets all the weights in the neural network NN to a random value in the range [-0.5,05].
	Input -> double vector<int>& modelTemplate
	Output -> void
	*/
    NN.resize(modelTemplate.size());
    for (int i = 0; (unsigned)i < modelTemplate.size() - 1; i++) {
        NN[i].resize(modelTemplate[i]);
        for (int j = 0; j < modelTemplate[i]; j++) {
            NN[i][j].resize(modelTemplate[i + 1]);
            for (int k = 0; k < modelTemplate[i + 1]; k++) {
                NN[i][j][k] = (double)rand() / RAND_MAX - 0.5;
            }
        }
    }
}