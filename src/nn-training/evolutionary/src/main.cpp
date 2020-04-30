#include <napi.h>
#include "./classwrapper_ModelTrainer.h"
#include "./classwrapper_NeuralNetwork.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    return ClassWrapper_ModelTrainer::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)
