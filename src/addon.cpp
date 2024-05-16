#include <node.h>

void TestAddon(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    v8::Isolate *isolate = args.GetIsolate();
    args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "Test tested :)").ToLocalChecked());
}

void Initialize(v8::Local<v8::Object> exports)
{
    NODE_SET_METHOD(exports, "testAddon", TestAddon);
}

NODE_MODULE(addon, Initialize)