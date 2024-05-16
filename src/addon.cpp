#include <iostream>
#include "napi.h"

Napi::String TestAddon(const Napi::CallbackInfo &args)
{
    Napi::Env env = args.Env();

    return Napi::String::New(env, "Test tested x2 :)");
}

// This method should receives: Number[], Number[], Number.
Napi::Value ProcessArrays(const Napi::CallbackInfo &args)
{
    Napi::Env env = args.Env();

    // Check if the args were passed
    if (args.Length() < 3)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    // Check the first one
    if (!args[0].IsArray())
    {
        Napi::TypeError::New(env, "First argument must be a number array").ThrowAsJavaScriptException();
        return env.Null();
    }
    // Check the second one
    if (!args[1].IsArray())
    {
        Napi::TypeError::New(env, "Second argument must be a number array").ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!args[2].IsNumber())
    {
        Napi::TypeError::New(env, "Third argument must be a number").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Array firstArray = args[0].As<Napi::Array>();
    Napi::Array secondArray = args[1].As<Napi::Array>();
    Napi::Number number = args[2].As<Napi::Number>();

    // Check the size of each array
    if (firstArray.Length() != 10)
    {
        Napi::TypeError::New(env, "The first array does not have a size of 10").ThrowAsJavaScriptException();
        return env.Null();
    }
    if (secondArray.Length() != 10)
    {
        Napi::TypeError::New(env, "The second array does not have a size of 10").ThrowAsJavaScriptException();
        return env.Null();
    }

    int min_array[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int max_array[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    float percent = 0;

    for (uint32_t i = 0; i < firstArray.Length(); i++)
    {
        Napi::Value item = firstArray.Get(i);
        if (item.IsNumber())
        {
            min_array[i] = item.As<Napi::Number>().Int32Value();
        }
        else
        {
            std::cerr << "First Array: Cannot parse non-numeric value of " << item.ToString().Utf8Value() << std::endl;
        }
    }

    for (uint32_t i = 0; i < secondArray.Length(); i++)
    {
        Napi::Value item = secondArray.Get(i);
        if (item.IsNumber())
        {
            max_array[i] = item.As<Napi::Number>().Int32Value();
        }
        else
        {
            std::cerr << "Second Array: Cannot parse non-numeric value of " << item.ToString().Utf8Value() << std::endl;
        }
    }

    percent = number.FloatValue();

    std::cout << firstArray.Length() << std::endl;
    std::cout << secondArray.Length() << std::endl;
    std::cout << number.FloatValue() << std::endl;

    // Simulate a procedure
    Napi::Object result = Napi::Object::New(env);
    result.Set("calc", 0.999);

    int sum_array[10];

    for (size_t i = 0; i < 10; i++)
    {
        sum_array[i] = max_array[i] - min_array[i];
    }

    Napi::Array sumArray = Napi::Array::New(env);
    for (size_t i = 0; i < 10; i++)
    {
        sumArray.Set(i, sum_array[i]);
    }

    result.Set("sum", sumArray);

    // return Napi::Object::New(env);
    return result;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "testAddon"), Napi::Function::New(env, TestAddon));
    exports.Set(Napi::String::New(env, "processArrays"), Napi::Function::New(env, ProcessArrays));
    return exports;
}

NODE_API_MODULE(addon, Init)