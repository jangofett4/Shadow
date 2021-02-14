#include <algorithm>

#include "LayerManager.hh"
#include "GameObject.hh"

Layer::Layer(std::string name) : Name(name), gameobjects() { }

void Layer::Render(const RenderContext& context)
{
    for (auto it = gameobjects.begin(); it != gameobjects.end(); it++)
        (*it)->Render(context);
}

void Layer::AddGameObject(GameObject* go)
{
    if (go->layer)
        go->layer->RemoveGameObject(go);
    go->layer = this;
    gameobjects.push_back(go);
}

void Layer::RemoveGameObject(GameObject* go)
{
    gameobjects.erase(
        std::find(gameobjects.begin(), gameobjects.end(), go)
    );
}

LayerManager::LayerManager() : layers() { }

LayerManager::~LayerManager()
{
    for (auto it = layers.begin(); it != layers.end(); it++)
        delete (*it);
}

Layer* LayerManager::AddLayer(std::string name)
{
    auto beg = layers.begin(), end = layers.end();
    auto layer = std::find_if(beg, end, [name](const Layer* l){ return l->Name == name; });
    if (layer != end)
        return nullptr;
    auto newlayer = new Layer(name);
    layers.push_back(newlayer);
    return newlayer;
}

Layer* LayerManager::GetLayer(std::string name)
{
    auto beg = layers.begin(), end = layers.end();
    auto layer = std::find_if(beg, end, [name](const Layer* l){ return l->Name == name; });
    if (layer == end)
        return nullptr;
    return (*layer);
}

void LayerManager::RenderForward(const RenderContext& context)
{
    for (auto it = layers.begin(); it != layers.end(); it++)
        (*it)->Render(context);
}

void LayerManager::RenderBackward(const RenderContext& context)
{
    for (auto it = layers.rbegin(); it != layers.rend(); it++)
        (*it)->Render(context);
}