#include "neuralNetwork.h"
#include <stdlib.h>
#include <iostream>

NeuralNetwork::NeuralNetwork() {
    NN = std::vector<std::vector<std::vector<double>>>();
}

void NeuralNetwork::get_NN(std::vector<std::vector<std::vector<double>>>& NN) {
    NN = this->NN;
}

std::vector<double> NeuralNetwork::matrixMultiplication(
    std::vector<double>& a,
    std::vector<std::vector<double>> b
) {
	std::cout << "start" << a.size() << " " << b.size() << " "<<b[0].size() << std::endl;
    std::vector<double> res(b[0].size(), 0);
    for (int i = 0; i < res.size(); i++)
        for (int j = 0; j < b.size(); j++)
            res[i] += a[j] * b[j][i];
	std::cout << "hello" << std::endl;
    return res;
}

void NeuralNetwork::predict(std::vector<double>& input, std::vector<double>& output) {
	std::vector<double> current = input;
	for (int layer = 0; layer < NN.size(); layer++) {
		for (int i = 0; i < current.size(); i++) {
			current[i] = activate(current[i]);
		}
		if (layer != NN.size() - 1)
            current = matrixMultiplication(current, NN[layer]);
	}
	output = current;
}

double NeuralNetwork::activate(double a) {
	return a;
}

void NeuralNetwork::modifyWeights(double mutationRange) {
    for (int i = 0; i < NN.size(); i++) {
        for (int j = 0; j < NN[i].size(); j++) {
            for (int k = 0; k < NN[i][j].size(); k++) {
                NN[i][j][k] += (double)(rand() % (int)(mutationRange * 1000000 * 2)) / 1000000 - mutationRange;
            }
        }
    }
}

void NeuralNetwork::generateRandomInstance(std::vector<int>& modelTemplate) {
    NN.resize(modelTemplate.size());
    for (int i = 0; i < modelTemplate.size() - 1; i++) {
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
