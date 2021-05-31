#pragma once
#include "LayerManager.hh"

#include <algorithm>

template<typename T>
Layer<T>::Layer(std::string name) : Name(name), objects() { }

template<typename T>
void Layer<T>::Render(RenderContext& context)
{
    for (auto it = objects.begin(); it != objects.end(); it++)
        (*it)->Render(context);
}

template<typename T>
void Layer<T>::Render(RenderContext& context, std::function<bool(T)> predicate)
{
    for (auto it = objects.begin(); it != objects.end(); it++)
        if (predicate((*it)))
            (*it)->Render(context);
}

template<typename T>
void Layer<T>::AddObject(T object)
{
    if (object->layer)
        object->layer->RemoveObject(object);
    object->layer = this;
    objects.push_back(object);
}

template<typename T>
void Layer<T>::RemoveObject(T object)
{
    auto found = std::find(objects.begin(), objects.end(), object);
    if (found != objects.end())
        objects.erase(found);
}

template<typename T>
LayerManager<T>::LayerManager() : layers() { }

template<typename T>
LayerManager<T>::~LayerManager()
{
    for (auto it = layers.begin(); it != layers.end(); it++)
        delete (*it);
}

template<typename T>
Layer<T>* LayerManager<T>::AddLayer(std::string name)
{
    auto beg = layers.begin(), end = layers.end();
    auto layer = std::find_if(beg, end, [name](const Layer<T>* l){ return l->Name == name; });
    if (layer != end)
        return nullptr;
    auto newlayer = new Layer<T>(name);
    layers.push_back(newlayer);
    return newlayer;
}

template<typename T>
Layer<T>* LayerManager<T>::GetLayer(std::string name)
{
    auto beg = layers.begin(), end = layers.end();
    auto layer = std::find_if(beg, end, [name](const Layer<T>* l){ return l->Name == name; });
    if (layer == end)
        return nullptr;
    return (*layer);
}

template<typename T>
void LayerManager<T>::RenderForward(RenderContext& context)
{
    for (auto it = layers.begin(); it != layers.end(); it++)
        (*it)->Render(context);
}

template<typename T>
void LayerManager<T>::RenderForward(RenderContext& context, std::function<bool(T)> predicate)
{
    for (auto it = layers.begin(); it != layers.end(); it++)
        (*it)->Render(context, predicate);
}

template<typename T>
void LayerManager<T>::RenderBackward(RenderContext& context)
{
    for (auto it = layers.rbegin(); it != layers.rend(); it++)
        (*it)->Render(context);
}

template<typename T>
void LayerManager<T>::RenderBackward(RenderContext& context, std::function<bool(T)> predicate)
{
    for (auto it = layers.rbegin(); it != layers.rend(); it++)
        (*it)->Render(context, predicate);
}