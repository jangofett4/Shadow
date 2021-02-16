#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "GameTime.hh"
#include "GameObject.hh"
#include "LayerManager.hh"
#include "RenderContext.hh"
#include "Components/Camera.hh"

using namespace std;

class Scene
{
    std::vector<GameObject*> gameObjects;
    LayerManager layerManager;

    Camera* mainCamera;

public:
    struct {
        Layer* UI;
        Layer* Default;
    } Layers;

    Scene();
    ~Scene();

    bool AddGameObject(GameObject*, Layer* = nullptr);
    bool RemoveGameObject(GameObject*);
    bool RemoveGameObject(std::string);
    void SetGameObjectLayer(GameObject*, Layer* = nullptr);

    bool SetMainCamera(std::string);
    Camera* GetMainCamera() const { return mainCamera; }

    std::vector<GameObject*>    GetGameObjectsWithTag(std::string);
    GameObject*                 GetGameObjectWithName(std::string);

    void SceneStart();
    void SceneUpdate(GameTime*);
    void SceneRender(RenderContext&);
};