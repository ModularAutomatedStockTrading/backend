#include "classwrapper.h"

Napi::FunctionReference ClassWrapper::constructor;

Napi::Object ClassWrapper::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "EvolutionaryModelTrainer", {
        /*InstanceMethod("add", &ClassWrapper::Add),*/
        InstanceMethod("Train", &ClassWrapper::Train())/*,*/
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("EvolutionaryModelTrainer", func);
    return exports;
}

ClassWrapper::ClassWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<ClassWrapper>(info)  {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();

    if (length != 7) {
        Napi::TypeError::New(env, "Expected 7 arguments").ThrowAsJavaScriptException();
    }

    Napi::Number arg1 = info[0].As<Napi::Number>();
    Napi::Array arg2 = info[1].As<Napi::Array>();
    Napi::Number arg3 = info[2].As<Napi::Number>();
    Napi::Number arg4 = info[3].As<Napi::Number>();
    Napi::Array arg5 = info[4].As<Napi::Array>();
    Napi::Number arg6 = info[5].As<Napi::Number>();
    Napi::Array arg7 = info[6].As<Napi::Array>();

    int layer_cnt = arg1.Int32Value();
    int data_point_cnt = arg3.Int32Value();
    int input_cnt = arg4.Int32Value();
    int output_cnt = arg6.Int32Value();

    int model[layer_cnt];
    for(int i = 0; i < arg2.Length(); i++) {
        Napi::Value value = arg2[i];
        if (value.IsNumber()) {
            model[i] = (int)value.As<Napi::Number>();
        } else {
            Napi::TypeError::New(env, "Expected an array of numbers").ThrowAsJavaScriptException();
        }
    }

    std::vector<std::vector<int>> input(std::vector<std::vector<int>>(data_point_cnt, std::vector<int>(input_cnt)));
    for(int i = 0; i < arg5.Length(); i++) {
        Napi::Value assumed_input_array = arg5[i];
        if(assumed_input_array.IsArray()){
            Napi::Array input_array = assumed_input_array.As<Napi::Array>();
            for(int j = 0; j < input_array.Length(); j++) {
                Napi::Value value = input_array[j];
                if (value.IsNumber()) {
                    input[i][j] = (int)value.As<Napi::Number>();
                } else {
                    Napi::TypeError::New(env, "Expected an array of numbers").ThrowAsJavaScriptException();
                }
            }
        }
    }

    std::vector<std::vector<int>> output(std::vector<std::vector<int>>(data_point_cnt, std::vector<int>(output_cnt)));
    for(int i = 0; i < arg7.Length(); i++) {
        Napi::Value assumed_output_array = arg7[i];
        if(assumed_output_array.IsArray()){
            Napi::Array output_array = assumed_output_array.As<Napi::Array>();
            for(int j = 0; j < output_array.Length(); j++) {
                Napi::Value value = output_array[j];
                if (value.IsNumber()) {
                    output[i][j] = (int)value.As<Napi::Number>();
                } else {
                    Napi::TypeError::New(env, "Expected an array of numbers").ThrowAsJavaScriptException();
                }
            }
        }
    }

    this->modelTrainer_ = new ModelTrainer(layer_cnt, model, input, output);
}

Napi::Value ClassWrapper::Train(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    //std::pair<double, double> mutationRate, int numberOfGenerations, int instancesPerGeneration

    int length = info.Length();

    if (length != 4) {
        Napi::TypeError::New(env, "Expected 4 arguments").ThrowAsJavaScriptException();
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
    if (!info[3].IsNumber()) {
        Napi::TypeError::New(env, "Number expected as forth argument").ThrowAsJavaScriptException();
    }

    std::pair<double, double> mutationRate = {(double)info[0].As<Napi::Number>(), (double)info[1].As<Napi::Number>()};
    int numberOfGenerations = (int)info[2].As<Napi::Number>();
    int instancesPerGeneration = (int)info[3].As<Napi::Number>();
    int id = this->modelTrainer_->train(mutationRate, numberOfGenerations, instancesPerGeneration);

    std::vector<std::vector<std::vector<int>>> model = this->modelTrainer_->get_model_NN();
    napi_value nn;
    napi_create_array(env, &nn);
    for (int i = 0; i < model.size(); i++) {
        napi_value nn_nodes;
        (napi_create_array(env, &nn_nodes);
        for (int j = 0; j < model[i].size(); j++) {
            napi_value nn_weights;
            napi_create_array(env, &nn_weights);
            for (int k = 0; k < model[i][j].size(); k++) {
                napi_set_element(env, nn_weights, i, Napi::Number::New(env, model[i][j][k]));
            }
            napi_set_element(env, nn_nodes, i, nn_weights);
        }
        napi_set_element(env, nn, i, nn_nodes);
    }

    return nn;
}

/*
Napi::Value ClassWrapper::Add(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (  info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    }

    Napi::Number toAdd = info[0].As<Napi::Number>();
    double answer = this->actualClass_->add(toAdd.DoubleValue());

    //return Napi::Number::New(env, num);
    return Napi::Number::New(info.Env(), answer);
}
*/
