
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
/*#include "neuralNetwork.h"

NeuralNetwork::NeuralNetwork() {
    NeuralNetwork::a = 5;
}*/
std::vector<std::vector<double>> mult(std::vector<std::vector<double>>& a, std::vector<std::vector<double>>& b) {
	std::vector<std::vector<double>> c(a.size(), std::vector<double>(b[0].size(), 0));
	for (int i = 0; i < c.size(); i++) {
		for (int j = 0; j < c[i].size(); j++) {
			for (int k = 0; k < b.size(); k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
			//print
			/*if (j == 0 && i > 0) { std::cout << '}' << '\n' << '\t' << '{' << c[i][j]; }
			else if (j == 0 && i == 0) { std::cout << '{' << '\n' << '\t' << '{' << c[i][j]; }
			else if (j > 0) { std::cout << ',' << ' ' << c[i][j]; };*/
		}
	}
	//print
	//std::cout << '}' << '\n' << '}' << ';';

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
				NN[i][j][k] = (double)(((std::rand() % 19) + 1) / 10.0); //random numbers between 0.1 to 1.9
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
	std::vector<std::vector<double>> prediction = predict(input, NN);
}

/*
#include "neuralNetwork.h"
#include <vector>
#include <iostream>
NeuralNetwork::NeuralNetwork() {
    int layer_count;
    std::vector<std::vector<std::vector<int>>> NN;
    std::vector<Layer> layers(layer_count, Layer::Layer());
    //hvert layer har x antal nodes og en 2D vektor weights med vægtene. layers[n].weights har dimensionerne layers[n+1].nodes.length x layers[n].nodes.length
    //hver node har en .in og .out værdi og en .activate() funktion som tager .in og returnere .out
    
    std::vector<std::vector<std::vector<int>>> generateRandomInstance(int layers, std::vector<int> nodesInLayers){ // returnere en neuralnetwork instance ud fra en model template med random weights
        std::vector<int> NN((layers -1), 0);
        for(int i; i < (layers -1)) {
            NN[i] = std::vector(nodesInLayers[i], 0);
            for(int j; j < nodesInLayers[i]) {
                NN[i][j] = std::vector(nodesInLayers[i+1], 0);
                std::cout << '[ ';
                for(int k; k < nodesInLayers[i+1]) {
                    NN[i][j][k] = (1 + (std::rand() % 20))/10; //random numbers between 0.1 to 1.9
                    std::cout << NN[i][j][k] << ' '; 
                }
                std::cout << ']' << '\n';
            }
        }
    }
    std::vector<int> predict(std::vector<int> inputVector) {
        for(int n; n < layes[1])
        for(int l;l<this.layers.length;l++) {
            
            
            for (int n; n<model.layers[l].nodes;n++){
                for (int w; w<model.layers[l].nodes[n].weights;w++) {
                this.layers[l].nodes[n].in = v[n]*this.layers[l].nodes[n].weights[w];
                this.layers[l].nodes[n].activate();//sætter node.out = activation(node.in) hvor activation fx. er ReLU
                }
            }


            v = layers[l].out()
        }


    }//køre en vector "igennem" den færdige model
}
NeuralNetwork::modifyWights(double upper, double lower) {}// modificere alle vægte med en random værdi mellem upper og lower 

class Node{
    Node() {
        int in;
        int out;
    }
    void activate(){
        this.out = ReLU(this.in)//ReLU er et eksempel
    }

};
class Layer{
    Layer(int intNodes) {
        int intNodes = intNodes;
        std::vector<Node> nodes(intNodes, Node());
        std::vector<int> in;
        std::vector<int> out;
        std::vector<std::vector<int>> weights;
    }
    void getIO() {
        for(int i;i<this.intNodes;i++) {
            this.in[i] = this.nodes[i].in;
            this.nodes[i].activate();
            this.out[i] = this.nodes[i].out;
        }
        
    }

};


instance = modelTemplate.generateRandomInstance()*/