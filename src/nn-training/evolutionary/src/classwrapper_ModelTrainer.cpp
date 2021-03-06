#include "classwrapper_ModelTrainer.h"
#include <iostream>

Napi::FunctionReference ClassWrapper_ModelTrainer::constructor;

void ClassWrapper_ModelTrainer::Init(Napi::Env env, Napi::Object& exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "EvolutionaryModelTrainer", {
        InstanceMethod("train", &ClassWrapper_ModelTrainer::Train)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("EvolutionaryModelTrainer", func);
}

ClassWrapper_ModelTrainer::ClassWrapper_ModelTrainer(const Napi::CallbackInfo& info) : Napi::ObjectWrap<ClassWrapper_ModelTrainer>(info)  {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();

    if (length != 8) {
        Napi::TypeError::New(env, "Expected 8 arguments").ThrowAsJavaScriptException();
    }

    Napi::Number arg1 = info[0].As<Napi::Number>();
    Napi::Array arg2 = info[1].As<Napi::Array>();
    Napi::Number arg3 = info[2].As<Napi::Number>();
    Napi::Number arg4 = info[3].As<Napi::Number>();
    Napi::Array arg5 = info[4].As<Napi::Array>();
    Napi::Number arg6 = info[5].As<Napi::Number>();
    Napi::Array arg7 = info[6].As<Napi::Array>();
    Napi::Boolean arg8 = info[7].As<Napi::Boolean>();

    int layer_cnt = arg1.Int32Value();
    int data_point_cnt = arg3.Int32Value();
    int input_cnt = arg4.Int32Value();
    int output_cnt = arg6.Int32Value();
    bool withBias = arg8.Value();

    std::vector<int> model(layer_cnt);
    for(int i = 0; (unsigned)i < arg2.Length(); i++) {
        Napi::Value value = arg2[i];
        if (value.IsNumber()) {
            model[i] = (int)value.As<Napi::Number>();
        } else {
            Napi::TypeError::New(env, "Expected an array of numbers").ThrowAsJavaScriptException();
        }
    }

    std::vector<std::vector<double>> input(std::vector<std::vector<double>>(data_point_cnt, std::vector<double>(input_cnt)));
    for(int i = 0; (unsigned)i < arg5.Length(); i++) {
        Napi::Value assumed_input_array = arg5[i];
        if(assumed_input_array.IsArray()){
            Napi::Array input_array = assumed_input_array.As<Napi::Array>();
            for(int j = 0; (unsigned)j < input_array.Length(); j++) {
                Napi::Value value = input_array[j];
                if (value.IsNumber()) {
                    input[i][j] = (double)value.As<Napi::Number>();
                } else {
                    Napi::TypeError::New(env, "Expected an array of numbers").ThrowAsJavaScriptException();
                }
            }
        }
    }
    std::vector<std::vector<double>> output(std::vector<std::vector<double>>(data_point_cnt, std::vector<double>(output_cnt)));
    for(int i = 0; (unsigned)i < arg7.Length(); i++) {
        Napi::Value assumed_output_array = arg7[i];
        if(assumed_output_array.IsArray()){
            Napi::Array output_array = assumed_output_array.As<Napi::Array>();
            for(int j = 0; (unsigned)j < output_array.Length(); j++) {
                Napi::Value value = output_array[j];
                if (value.IsNumber()) {
                    output[i][j] = (double)value.As<Napi::Number>();
                } else {
                    Napi::TypeError::New(env, "Expected an array of numbers").ThrowAsJavaScriptException();
                }
            }
        }
    }

    this->modelTrainer_ = new ModelTrainer(model, input, output, withBias);
}

Napi::Value ClassWrapper_ModelTrainer::Train(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();

    if (length != 3) {
        Napi::TypeError::New(env, "Expected 3 arguments").ThrowAsJavaScriptException();
    }

    if (!info[0].IsNumber()) {
        Napi::TypeError::New(env, "Number expected as first argument").ThrowAsJavaScriptException();
    }
    if (!info[1].IsNumber()) {
        Napi::TypeError::New(env, "Number expected as second argument").ThrowAsJavaScriptException();
    }
    if (!info[2].IsNumber()) {
        Napi::TypeError::New(env, "Number expected as third argument").ThrowAsJavaScriptException();
    }

    double mutationRange = (double)info[0].As<Napi::Number>();
    int numberOfGenerations = (int)info[1].As<Napi::Number>();
    int instancesPerGeneration = (int)info[2].As<Napi::Number>();

    int id = this->modelTrainer_->train(mutationRange, numberOfGenerations, instancesPerGeneration);

    std::vector<std::vector<std::vector<double>>> model;
    this->modelTrainer_->get_model(id, model);
    napi_value nn;
    napi_create_array(env, &nn);
    for (int i = 0; (unsigned)i < model.size(); i++) {
        napi_value nn_nodes;
        napi_create_array(env, &nn_nodes);
        for (int j = 0; (unsigned)j < model[i].size(); j++) {
            napi_value nn_weights;
            napi_create_array(env, &nn_weights);
            for (int k = 0; (unsigned)k < model[i][j].size(); k++) {
                napi_set_element(env, nn_weights, k, Napi::Number::New(env, model[i][j][k]));
            }
            napi_set_element(env, nn_nodes, j, nn_weights);
        }
        napi_set_element(env, nn, i, nn_nodes);
    }

    return Napi::Value(env, nn);
}
