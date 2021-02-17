#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include <string>

#include "Scene.hh"
#include "GameTime.hh"
#include "GameObject.hh"
#include "LayerManager.hh"
#include "Components/Camera.hh"

using namespace glm;

Scene::Scene() : gameObjects(), layerManager(), mainCamera(nullptr)
{   
    Layers.UI = layerManager.AddLayer("UI");
    Layers.Default = layerManager.AddLayer("Default");
}

Scene::~Scene()
{
    std::cout << "[Scene] Destroying " << gameObjects.size() << " gameobjects..." << std::endl;
    for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
        delete (*it);
}

bool Scene::AddGameObject(GameObject* go, Layer<GameObject*>* layer)
{
    for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
        if ((*it)->Name == go->Name)
            return false;

    gameObjects.push_back(go);
    if (!layer)
        layer = Layers.Default;
    layer->AddObject(go);

    return true;
}

bool Scene::RemoveGameObject(GameObject* go)
{
    for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
        if (*it == go)
        {
            gameObjects.erase(it);
            return true;
        }
    return false;
}

void Scene::SetGameObjectLayer(GameObject* go, Layer<GameObject*>* layer)
{
    layer->AddObject(go); // switching is automatically done by layer
}

bool Scene::SetMainCamera(std::string name)
{
    auto camgo = GetGameObjectWithName(name);
    if (!camgo)
        return false;
    auto cam = camgo->GetComponent<Camera>();
    if (!cam)
        return false;
    mainCamera = cam;
    return true;
}

bool Scene::RemoveGameObject(std::string name)
{
    for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
        if ((*it)->Name == name)
        {
            gameObjects.erase(it);
            return true;
        }
    return false;
}

std::vector<GameObject*> Scene::GetGameObjectsWithTag(std::string tag)
{
    std::vector<GameObject*> result;

    for (auto go = gameObjects.begin(); go != gameObjects.end(); go++)
        if ((*go)->Name == tag)
        {
            result.push_back(*go);
        }
    return result;
}

GameObject* Scene::GetGameObjectWithName(std::string name)
{
    for (auto go = gameObjects.begin(); go != gameObjects.end(); go++)
        if ((*go)->Name == name)
            return *go;
    return nullptr;
}

void Scene::SceneStart()
{
    for (auto go = gameObjects.begin(); go != gameObjects.end(); go++)
        (*go)->ComponentStart();
}

void Scene::SceneUpdate(GameTime* time)
{
    for (auto go = gameObjects.begin(); go != gameObjects.end(); go++)
        (*go)->ComponentUpdate(time);
}

void Scene::SceneRender(RenderContext& context)
{
    if (!mainCamera)
        return;
    layerManager.RenderBackward(context);
}