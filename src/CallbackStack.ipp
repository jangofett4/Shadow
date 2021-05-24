#include "CallbackStack.hh"

template<typename T>
CallbackStack<T>::CallbackStack() : callbacks() { }
template<typename T>
CallbackStack<T>::~CallbackStack() { }

template<typename T>
void CallbackStack<T>::CallAll(T* arg)
{
    for (auto it = callbacks.begin(); it != callbacks.end(); it++)
        (*it)(arg);
}

template<typename T>
void CallbackStack<T>::Subscribe(std::function<void(T*)> callback)
{
    callbacks.push_back(callback);
}