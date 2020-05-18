#include <iostream>
#include <vector>
#include <string>
#include <Ctime>

std::vector<std::vector<double>> mult(std::vector<std::vector<double>>& a, std::vector<std::vector<double>>& b) {
	std::vector<std::vector<double>> c(a.size(), std::vector<double>(b[0].size(), 0));
	for (int i = 0; i < c.size(); i++)
		for (int j = 0; j < c[i].size(); j++)
			for (int k = 0; k < b.size(); k++)
				c[i][j] += a[i][k] * b[k][j];
	return c;
}

double activate(double a) {
	return a;
}

std::vector<std::vector<std::vector<double>>> generateRandomInstance(int layers, std::vector<int> nodesInLayers) { // returnere en neuralnetwork instance ud fra en model template med random weights
	std::vector<std::vector<std::vector<double>>> NN(layers - 1, std::vector<std::vector<double>>(1, std::vector<double>(1, 0)));
	for (int i = 0; i < (layers - 1); i++) {
		NN[i] = std::vector<std::vector<double>>(nodesInLayers[i], std::vector<double>());
		for (int j = 0; j < nodesInLayers[i]; j++) {
			NN[i][j] = std::vector<double>(nodesInLayers[i + 1], 0);
			std::cout << '[' << ' ';
			for (int k = 0; k < nodesInLayers[i + 1]; k++) {
				NN[i][j][k] = (std::rand() % 19 + 1) / (double)10; //random numbers between 0.1 to 1.9
				std::cout << NN[i][j][k] << ' ';
			}
			std::cout << ']' << '\n';
		}
	}
	return NN;
}
std::vector<std::vector<double>> predict(std::vector<std::vector<double>> input, std::vector<std::vector<std::vector<double>>> NN) {
	std::vector<std::vector<double>> in = input;
	for (int l = 0; l < NN.size(); l++) {
		std::vector<std::vector<double>> out = in;
		for (int i = 0; i < in[0].size(); i++) {
			out[0][i] = activate(in[0][i]);
		}
		in = mult(out, NN[l]);
	}

	for(int a = 0; a < in[0].size(); a++) {
		std::cout << '[';
		for(int b = 0; b < input[0].size() -1; b++) {
			std::cout << input[0][b] << ", ";
		}
		std::cout << input[0][input[0].size()-1] << "] --> " << in[0][a];
	}
	return in;
}

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