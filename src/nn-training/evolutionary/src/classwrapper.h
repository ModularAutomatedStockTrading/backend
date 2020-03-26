#ifndef CLASSWRAPPER_H_INCLUDED
#define CLASSWRAPPER_H_INCLUDED

#include "napi.h"
#include "modelTrainer.h"

class ClassWrapper : public Napi::ObjectWrap<ClassWrapper> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports); //Init function for setting the export key to JS
    ClassWrapper(const Napi::CallbackInfo& info); //Constructor to initialise

private:
    static Napi::FunctionReference constructor; //reference to store the class definition that needs to be exported to JS
    Napi::Value GetInputSize(const Napi::CallbackInfo& info); //wrapped getInputSize function
    //Napi::Value Add(const Napi::CallbackInfo& info); //wrapped add function
    ModelTrainer *modelTrainer_; //internal instance of modelTrainer used to perform actual operations.
};

#endif // CLASSWRAPPER_H_INCLUDED
