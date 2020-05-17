#include <math.h> 
#include <iostream>
#include <stdio.h>
#include <string>
#ifndef ACTIVATION_INCLUDED
#define ACTIVATION_INCLUDED

namespace Activation{
	/*
	'Activates' an input, a, via the identity activation function and returns the output.
	(this activation function doesn't do anything by design)
	Input -> double a
	Output -> double a
	*/
	double identityActivate(double a) {
		return a;
	}
	/*
	'Activates' an input, a, via the ReLU activation function and returns the output.
	Input -> double a
	Output -> double a
	*/
	double ReLUActivate(double a) {
		if (a <= 0) { return 0; }
		return a;
	}
	/*
	'Activates' an input, a, via the binary step activation function and returns the output.
	Input -> double a
	Output -> double a
	*/
	double binaryStepActivate(double a) {
		if (a < 0) { return 0; }
		return 1;
	}
	/*
	'Activates' an input, a, via the logistic activation function and returns the output.
	Input -> double a
	Output -> double a
	*/
	double logisticActivate(double a) {
		return 1/(1 + exp(-a));
	}
	/*
	'Activates' an input, a, via the tanH activation function and returns the output.
	Input -> double a
	Output -> double a
	*/
	double tanHActivate(double a) {
		return (exp(a) - exp(-a))/(exp(a) + exp(-a));
	}
	/*
	'Activates' an input, a, via the SQNL activation function and returns the output.
	Input -> double a
	Output -> double a
	*/
	double SQNLActivate(double a) {
		if (a < -2) { return -1; }
		if (a < 0) { return a + (a*a)/4; }
		if (a <= 2) { return a - (a*a)/4; }
		return 1;
	}
	/*
	'Activates' an input, a, via the soft sign activation function and returns the output.
	Input -> double a
	Output -> double a
	*/
	double softsignActivate(double a) {
		return a/(1 + abs(a));
	}
	/*
	'Activates' an input, a, via the ISRU activation function and returns the output.
	Input -> double a
	Output -> double a
	*/
	double ISRUActivate(double a) {
		double b = 1; // Must be larger than 0
		return a/sqrt(1.0 + b*a*a); //Retuns value in range [-1/sqrt(b),1/sqrt(b)]
	}
	/*
	Calls an activation function specified in the input. 
	Input -> double a, string activationType.
	Output -> double a
	
	*/
	double activate(double a, std::string activationType) { 
		if 		(activationType == "identity")   return identityActivate(a);
		else if (activationType == "ReLU")	     return ReLUActivate(a);
		else if (activationType == "binaryStep") return binaryStepActivate(a);
		else if (activationType == "logistic")	 return logisticActivate(a);
		else if (activationType == "tanH")		 return tanHActivate(a);
		else if (activationType == "SQNL")		 return SQNLActivate(a);
		else if (activationType == "softsign")	 return softsignActivate(a);
		else if (activationType == "ISRU")		 return ISRUActivate(a);
		return -1000;
	}
}

#endif 
