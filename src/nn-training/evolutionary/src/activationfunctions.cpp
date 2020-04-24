#include <math.h> 

#ifndef ACTIVATION_INCLUDED
#define ACTIVATION_INCLUDED

namespace Activation{
	double identityActivate(double a) {
		return a;
	}

	double ReLUActivate(double a) {
		if (a <= 0) { return 0; }
		return a;
	}

	double binaryStepActivate(double a) {
		if (a < 0) { return 0; }
		return 1;
	}

	double logisticActivate(double a) {
		return 1/(1 + exp(-a));
	}

	double tanHActivate(double a) {
		return (exp(a) - exp(-a))/(exp(a) + exp(-a));
	}

	double SQNLActivate(double a) {
		if (a < -2) { return -1; }
		if (a < 0) { return a + (a*a)/4; }
		if (a <= 2) { return a - (a*a)/4; }
		return 1;
	}

	double softsignActivate(double a) {
		return a/(1 + abs(a));
	}
}

#endif 
/*
double ISRUActivate(double a) {
	return a/(1 + sqrt(1+));
}
*/