#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "RenderContext.hh"

class GameObject;

using namespace glm;

class Layer
{
    friend class Scene;
    std::vector<GameObject*> gameobjects;
public:
    const std::string Name;

    Layer(std::string);

    void Render(const RenderContext& context);
private:
    void AddGameObject(GameObject*);
    void RemoveGameObject(GameObject*);
};

class LayerManager
{
    std::vector<Layer*> layers;
public:

    LayerManager();
    ~LayerManager();

    Layer* AddLayer(std::string);
    Layer* GetLayer(std::string);

    void RenderForward(const RenderContext&);
    void RenderBackward(const RenderContext&);
};