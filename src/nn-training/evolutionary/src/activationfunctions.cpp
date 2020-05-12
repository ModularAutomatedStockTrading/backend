#include <math.h> 
#include <iostream>
#include <stdio.h>
#ifndef ACTIVATION_INCLUDED
#define ACTIVATION_INCLUDED

namespace Activation{
	double activate(double a, char activationType[]) {
		if 		(activationType == "identity")	{return identityActivate(a);}
		else if (activationType == "ReLU")		{return ReLUActivate(a);}
		else if (activationType == "binaryStep"){return binaryStepActivate(a);}
		else if (activationType == "logistic")	{return logisticActivate(a);}
		else if (activationType == "tanH")		{return tanHActivate(a);}
		else if (activationType == "SQNL")		{return SQNLActivate(a);}
		else if (activationType == "softsign")	{return softsignActivate(a);}
		else if (activationType == "ISRU")		{return ISRUActivate(a);}	
	}

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

	double ISRUActivate(double a) {
		return a/(1 + sqrt(1+abs(a)));
	}

	
}

#endif 


