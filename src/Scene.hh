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
    LayerManager<GameObject*> layerManager;

    Camera* mainCamera;

public:
    struct {
        Layer<GameObject*>* UI;
        Layer<GameObject*>* Default;
    } Layers;

    Scene();
    ~Scene();

    bool AddGameObject(GameObject*, Layer<GameObject*>* = nullptr);
    bool RemoveGameObject(GameObject*);
    bool RemoveGameObject(std::string);
    void SetGameObjectLayer(GameObject*, Layer<GameObject*>* = nullptr);

    bool SetMainCamera(std::string);
    Camera* GetMainCamera() const { return mainCamera; }

    std::vector<GameObject*>    GetGameObjectsWithTag(std::string);
    GameObject*                 GetGameObjectWithName(std::string);

    void SceneStart();
    void SceneUpdate(GameTime*);
    void SceneRender(RenderContext&);
};