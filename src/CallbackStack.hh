#pragma once

#include <vector>
#include <functional>

// A basic class to create a callback list and execute all at once with same arguments
// Mainly useful for events
template<typename T>
class CallbackStack
{
    // Callback list
    // C++ didnt like it when I used pure functor (void(T*)), so I had to use std::function
    std::vector<std::function<void(T*)>> callbacks;
public:

    CallbackStack();
    ~CallbackStack();

    void CallAll(T* arg);

    virtual void Subscribe(std::function<void(T*)> callback);

    void operator()(T* arg);
    void operator()(std::function<void(T*)> callback);
};

#include "CallbackStack.ipp"