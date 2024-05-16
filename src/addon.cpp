#include "napi.h"

Napi::String TestAddon(const Napi::CallbackInfo &args)
{
    Napi::Env env = args.Env();

    return Napi::String::New(env, "Test tested x2 :)");
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "testAddon"), Napi::Function::New(env, TestAddon));
    return exports;
}

NODE_API_MODULE(addon, Init)