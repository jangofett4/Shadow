#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <string>

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

    void RenderForward(RenderContext&);
    void RenderBackward(RenderContext&);
};

#include "LayerManager.ipp"