#pragma once

#include <string>

#include "../GameTime.hh"

class GameObject;

class Component
{
public:
    virtual const std::string Name();
    GameObject* Parent;

    virtual ~Component();
};

class ShouldUpdate
{
public:
    virtual void Start() = 0;
    virtual void Update(GameTime*) = 0;
};