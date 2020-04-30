#include <napi.h>
#include "./classwrapper_ModelTrainer.h"
#include "./classwrapper_NeuralNetwork.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    ClassWrapper_NeuralNetwork::Init(env, exports);
    ClassWrapper_ModelTrainer::Init(env, exports);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)
