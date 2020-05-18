#include "classwrapper_NeuralNetwork.h"
#include <iostream>

Napi::FunctionReference ClassWrapper_NeuralNetwork::constructor;

void ClassWrapper_NeuralNetwork::Init(Napi::Env env, Napi::Object& exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "NNExecutor", {
        InstanceMethod("predict", &ClassWrapper_NeuralNetwork::Predict)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("NNExecutor", func);
}

ClassWrapper_NeuralNetwork::ClassWrapper_NeuralNetwork(const Napi::CallbackInfo& info) : Napi::ObjectWrap<ClassWrapper_NeuralNetwork>(info)  {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();
    if (length != 3) {
        Napi::TypeError::New(env, "Expected 3 arguments").ThrowAsJavaScriptException();
    }

    int layer_cnt = info[0].As<Napi::Number>().Int32Value();
    Napi::Array model = info[1].As<Napi::Array>();
    bool withBias = info[2].As<Napi::Boolean>().Value();

    std::vector<std::vector<std::vector<double>>> NN(layer_cnt);
    for(int i = 0; i < layer_cnt; i++) {
        Napi::Value maybe_model_i = model[i];
        if(maybe_model_i.IsArray()){
            Napi::Array model_i = maybe_model_i.As<Napi::Array>();
            NN[i].resize(model_i.Length());
            for(int j = 0; (unsigned)j < NN[i].size(); j++) {
                Napi::Value maybe_model_i_j = model_i[j];
                if(maybe_model_i_j.IsArray()){
                    Napi::Array model_i_j = maybe_model_i_j.As<Napi::Array>();
                    NN[i][j].resize(model_i_j.Length());
                    for(int k = 0; (unsigned)k < NN[i][j].size(); k++) {
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
    this->neuralNetwork_->set_NN(NN);
}

Napi::Value ClassWrapper_NeuralNetwork::Predict(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();
    if (length != 3) {
        Napi::TypeError::New(env, "Expected 3 arguments").ThrowAsJavaScriptException();
    }

    int input_size = info[0].As<Napi::Number>().Int32Value();
    int output_size = info[1].As<Napi::Number>().Int32Value();
    Napi::Array input = info[2].As<Napi::Array>();

    std::vector<double> a(input_size);
    std::vector<double> b(output_size);

    for(int i = 0; i < input_size; i++) {
        Napi::Value value = input[i];
        if (value.IsNumber()) {
            a[i] = (double)value.As<Napi::Number>();
        } else {
            Napi::TypeError::New(env, "Expected an array of numbers").ThrowAsJavaScriptException();
        }
    }

    this->neuralNetwork_->predict(a, b);

    napi_value output;
    napi_create_array(env, &output);
    for (int i = 0; (unsigned)i < b.size(); i++) {
        napi_set_element(env, output, i, Napi::Number::New(env, b[i]));
    }

    return Napi::Value(env, output);
}
