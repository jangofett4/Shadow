#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <functional>

#include "RenderContext.hh"

class GameObject;

using namespace glm;

template<typename T>
class Layer
{
    std::vector<T> objects;
public:
    const std::string Name;

    Layer(std::string);

    void Render(RenderContext& context);
    void Render(RenderContext& context, std::function<bool(T)> predicate);

    void AddObject(T);
    void RemoveObject(T);
};

template<typename T>
class LayerManager
{
    std::vector<Layer<T>*> layers;
public:

    LayerManager();
    ~LayerManager();

    Layer<T>* AddLayer(std::string);
    Layer<T>* GetLayer(std::string);

    void RenderForward(RenderContext& context);
    void RenderForward(RenderContext& context, std::function<bool(T)> predicate);

    void RenderBackward(RenderContext& context);
    void RenderBackward(RenderContext& context, std::function<bool(T)> predicate);
};

#include "LayerManager.ipp"