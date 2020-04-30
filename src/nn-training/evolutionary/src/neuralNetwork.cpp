#include "neuralNetwork.h"
#include <stdlib.h>
#include <iostream>
#include "activationfunctions.cpp"

NeuralNetwork::NeuralNetwork(bool withBias) {
    NN = std::vector<std::vector<std::vector<double>>>();
	this->withBias = withBias;
}

void NeuralNetwork::get_NN(std::vector<std::vector<std::vector<double>>>& NN) {
    NN = this->NN;
}

std::vector<double> NeuralNetwork::matrixMultiplication(
    std::vector<double>& a,
    std::vector<std::vector<double>> b
) {
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
	std::vector<double> current = input;
	for (int layer = 0; (unsigned)layer < NN.size() - 1; layer++) {
		current = matrixMultiplication(current, NN[layer]);
		for (int i = 0; (unsigned)i < current.size(); i++) {
			if((unsigned) layer == NN.size() - 2) current[i] = Activation::SQNLActivate(current[i]);
			else current[i] = Activation::logisticActivate(current[i]);
		}
	}
	output = current;
}

void NeuralNetwork::modifyWeights(double mutationRange) {
    for (int i = 0; (unsigned)i < NN.size(); i++) {
        for (int j = 0; (unsigned)j < NN[i].size(); j++) {
            for (int k = 0; (unsigned)k < NN[i][j].size(); k++) {
                NN[i][j][k] += (double)(rand() % (int)(mutationRange * 1000000 * 2)) / 1000000 - mutationRange;
            }
        }
    }
}

void NeuralNetwork::generateRandomInstance(std::vector<int>& modelTemplate) {
    NN.resize(modelTemplate.size());
    for (int i = 0; (unsigned)i < modelTemplate.size() - 1; i++) {
        NN[i].resize(modelTemplate[i]);
        for (int j = 0; j < modelTemplate[i]; j++) {
            NN[i][j].resize(modelTemplate[i + 1]);
            for (int k = 0; k < modelTemplate[i + 1]; k++) {
                NN[i][j][k] = (double)rand() / RAND_MAX;
            }
        }
    }
}

/*
int main()
{
	std::srand(time(NULL));
	std::vector<int> nodesInLayers(3, 0);
	nodesInLayers[0] = 4;
	nodesInLayers[1] = 2;
	nodesInLayers[2] = 1;
	std::vector<std::vector<std::vector<double>>> NN = generateRandomInstance(3, nodesInLayers);
	std::vector<std::vector<double>> input(1, std::vector<double>(4, 0.0));
	input[0][0] = 1;
	input[0][1] = 2;
	input[0][2] = 3;
	input[0][3] = 4;

    //set NN to test NN = [[[1.1, 1.2], [1.3, 0.2], [1.2, 1.2], [1.3, 3.4]], [[0.9], [1.0]]] remember to set nodesInLayers = [4, 2, 1], predict should be 30.05 with input [[1, 2, 3, 4]]
	//int l = 0;
	//double n[] = { 1.1, 1.2, 1.3, 0.2, 1.2, 1.2, 1.3, 3.4, 0.9, 1.0 };
	//for (int i = 0; i < NN.size(); i++) {
	//	for (int j = 0; j < NN[i].size(); j++) {
	//		for (int k = 0; k < NN[i][j].size(); k++) {
	//			NN[i][j][k] = n[l];
	//			l++;
	//		}
	//	}
	//}

	std::vector<std::vector<double>> prediction = predict(input, NN);
}
*/
