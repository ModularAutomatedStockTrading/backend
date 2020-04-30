#ifndef CLASSWRAPPER_NEURALNETWORK_H_INCLUDED
#define CLASSWRAPPER_NEURALNETWORK_H_INCLUDED

#include <napi.h>
#include "neuralNetwork.h"

class ClassWrapper_NeuralNetwork : public Napi::ObjectWrap<ClassWrapper_NeuralNetwork> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports); //Init function for setting the export key to JS
    ClassWrapper_NeuralNetwork(const Napi::CallbackInfo& info); //Constructor to initialise

private:
    static Napi::FunctionReference constructor; //reference to store the class definition that needs to be exported to JS
    Napi::Value Predict(const Napi::CallbackInfo& info); //wrapped predict function
    NeuralNetwork* neuralNetwork_; //internal instance of neuralNetwork used to perform actual operations.
};

#endif // CLASSWRAPPER_NEURALNETWORK_H_INCLUDED
