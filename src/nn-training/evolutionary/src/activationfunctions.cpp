#include "neuralNetwork.h"

double NeuralNetwork::identityActivate(double a) {
	return a;
}

double NeuralNetwork::ReLUActivate(double a) {
	if (a <= 0) { return 0; }
	return a;
}

double NeuralNetwork::binaryStepActivate(double a) {
	if (a < 0) { return 0; }
	return 1;
}

double NeuralNetwork::logisticActivate(double a) {
	return 1/(1 + exp(-a));
}

double NeuralNetwork::tanHActivate(double a) {
	return (exp(a) - exp(-a))/(exp(a) + exp(-a));
}

double NeuralNetwork::binaryStepActivate(double a) {
	if (a < -2) { return -1; }
	if (a < 0) { return a + (a*a)/4; }
	if (a <= 2) { return a - (a*a)/4; }
	return 1;
}

double NeuralNetwork::softsignActivate(double a) {
	return a/(1 + abs(a));
}
/*
double NeuralNetwork::ISRUActivate(double a) {
	return a/(1 + sqrt(1+));
}
*/