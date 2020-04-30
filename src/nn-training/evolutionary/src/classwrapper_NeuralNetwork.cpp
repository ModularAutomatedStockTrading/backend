#include "classwrapper_NeuralNetwork.h"
#include <iostream>

Napi::FunctionReference ClassWrapper_NeuralNetwork::constructor;

Napi::Object ClassWrapper_NeuralNetwork::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "NN_Executor", {
        InstanceMethod("predict", &ClassWrapper_NeuralNetwork::Predict)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("NN_Executor", func);

    return exports;
}

ClassWrapper_NeuralNetwork::ClassWrapper_NeuralNetwork(const Napi::CallbackInfo& info) : Napi::ObjectWrap<ClassWrapper_NeuralNetwork>(info)  {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();
    if (length != 5) {
        Napi::TypeError::New(env, "Expected 5 arguments").ThrowAsJavaScriptException();
    }

    int a = info[0].As<Napi::Number>().Int32Value();
    int b = info[1].As<Napi::Number>().Int32Value();
    int b = info[2].As<Napi::Number>().Int32Value();
    Napi::Array model = info[3].As<Napi::Array>();
    bool withBias = info[4].As<Napi::Boolean>().Value();

    std::vector<std::vector<std::vector<double>>> NN(
        a,
        std::vector<std::vector<double>>(b, std::vector<double>(c))
    );
    for(int i = 0; i < a; i++) {
        Napi::Value maybe_model_i = model[i];
        if(maybe_model_i.IsArray()){
            Napi::Array model_i = maybe_model_i.As<Napi::Array>();
            for(int j = 0; j < b; j++) {
                Napi::Value maybe_model_i_j = model_i[j];
                if(maybe_model_i_j.IsArray()){
                    Napi::Array model_i_j = maybe_model_i_j.As<Napi::Array>();
                    for(int k = 0; k < c; k++) {
                        Napi::Value value = model_i_j[k];
                        if (value.IsNumber()) {
                            NN[i][j][k] = (double)value.As<Napi::Number>();
                        } else {
                            Napi::TypeError::New(env, "Expected an array of numbers").ThrowAsJavaScriptException();
                        }
                    }
                }
            }
        }
    }

    this->neuralNetwork_ = new NeuralNetwork(withBias);
    this->neuralNetwork_.set_NN(NN);
}

Napi::Value ClassWrapper_NeuralNetwork::Predict(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();
    if (length != 1) {
        Napi::TypeError::New(env, "Expected 1 arguments").ThrowAsJavaScriptException();
    }

    int input_size = info[0].As<Napi::Number>().Int32Value();
    int output_size = info[1].As<Napi::Number>().Int32Value();
    Napi::Array input = info[2].As<Napi::Array>();

    std::vector<int> a(input_size);
    std::vector<double> b(output_size);

    for(int i = 0; i < input_size; i++) {
        Napi::Value value = input[i];
        if (value.IsNumber()) {
            a[i] = (int)value.As<Napi::Number>();
        } else {
            Napi::TypeError::New(env, "Expected an array of numbers").ThrowAsJavaScriptException();
        }
    }

    this.neuralNetwork_->predict(a, b);

    napi_value output;
    napi_create_array(env, &output);
    for (int i = 0; (unsigned)i < b.size(); i++) {
        napi_value value;
        napi_set_element(env, output, i, value);
    }

    return Napi::Value(env, output);
}
