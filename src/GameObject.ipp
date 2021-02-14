#pragma once

#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include "Components/Component.hh"

template<typename T>
T* GameObject::GetComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "GetComponent requires a generic parameter with Component type");
    auto it = components.find(std::type_index(typeid(T)));
    if (it == components.end())
        return nullptr;
    return static_cast<T*>(it->second);
}

template<typename T>
bool GameObject::AddComponent(T* component)
{
    static_assert(std::is_base_of<Component, T>::value, "AddComponent requires a generic parameter with Component type");
    bool result = components.emplace(std::type_index(typeid(T)), component).second;
    component->Parent = this;
    if (result && std::is_base_of<class ShouldUpdate, T>::value) // Needs Starting & Updating
        updateNeeded.push_back((ShouldUpdate*)component); // Had to use reinterpret_cast here, its dangerous but I sure as hell know its correct type
    if (result && std::is_base_of<class Renderer, T>::value) // TODO: ugly?
        renderers.push_back(reinterpret_cast<class Renderer*>(component));
    return result;
}