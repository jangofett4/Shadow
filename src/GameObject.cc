#include <typeinfo>
#include <iostream>
#include <algorithm>

#include <glm/glm.hpp>

#include "Components/Renderer.hh"
#include "Components/Renderer3D.hh"

#include "GameObject.hh"
#include "GameTime.hh"

using namespace glm;

GameObject::GameObject(const char* name) : Name(name), Tag(""), components(), updateNeeded(), children(), renderers(), parent(nullptr), layer(nullptr)
{
    transform = new Transform();
    AddComponent(transform);
}

GameObject::~GameObject() 
{
    for (auto it = components.begin(); it != components.end(); it++)
    {
        auto ptr = (*it).second;
        delete ptr;
    }
}

void GameObject::ComponentStart()
{
    for (auto it = children.begin(); it != children.end(); it++)
        (*it)->ComponentStart();

    for (auto i = updateNeeded.begin(); i != updateNeeded.end(); i++)
        (*i)->Start();
    
    // TODO: BAD
    auto r3d = GetComponent<Renderer3D>();
    if (r3d) r3d->Setup();
}

void GameObject::ComponentUpdate(GameTime* time)
{
    for (auto i = updateNeeded.begin(); i != updateNeeded.end(); i++)
        (*i)->Update(time);
}

bool GameObject::AddChildren(GameObject* go)
{
    auto beg = children.begin(), end = children.end();
    auto it = std::find_if(
        beg,
        end,
        [go](const GameObject* x){ return go->Name == x->Name; }
    );
    if (it != end)
        return false;
    children.push_back(go);
    return true;
}

void GameObject::Render(const RenderContext context)
{
    for (auto it = renderers.begin(); it != renderers.end(); it++)
        (*it)->Render(context);
}