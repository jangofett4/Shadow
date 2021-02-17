#pragma once

#include <glm/glm.hpp>

#include <string>
#include <typeinfo>
#include <typeindex>
#include <vector>
#include <unordered_map>

#include "GameTime.hh"
#include "RenderContext.hh"
#include "LayerManager.hh"
#include "Components/Component.hh"
#include "Components/Renderer.hh"
#include "Components/Transform.hh"

using namespace glm;

class GameObject
{
    friend class Scene;

    std::unordered_map<std::type_index, Component*> components;
    std::vector<ShouldUpdate*> updateNeeded;
    std::vector<GameObject*> children;
    GameObject* parent;

    std::vector<Renderer*> renderers;

public:
    const std::string Name;
    std::string Tag;
    Layer<GameObject*>* layer;

    Transform* transform;

    GameObject(const char*);
    ~GameObject();
    
    template<typename T> T* GetComponent();
    template<typename T> bool AddComponent(T*);

    void ComponentStart();
    void ComponentUpdate(GameTime*);

    bool AddChildren(GameObject*);

    void Render(RenderContext&);
};

#include "GameObject.ipp"