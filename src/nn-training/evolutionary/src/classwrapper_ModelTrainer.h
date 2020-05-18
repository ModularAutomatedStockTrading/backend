#ifndef CLASSWRAPPER_MODELTRAINER_H_INCLUDED
#define CLASSWRAPPER_MODELTRAINER_H_INCLUDED

#include <napi.h>
#include "modelTrainer.h"

class ClassWrapper_ModelTrainer : public Napi::ObjectWrap<ClassWrapper_ModelTrainer> {
public:
    static void Init(Napi::Env env, Napi::Object& exports); //Init function for setting the export key to JS
    ClassWrapper_ModelTrainer(const Napi::CallbackInfo& info); //Constructor to initialise

private:
    static Napi::FunctionReference constructor; //reference to store the class definition that needs to be exported to JS
    Napi::Value Train(const Napi::CallbackInfo& info); //wrapped train function
    ModelTrainer* modelTrainer_; //internal instance of modelTrainer used to perform actual operations.
};

#endif // CLASSWRAPPER_MODELTRAINER_H_INCLUDED
