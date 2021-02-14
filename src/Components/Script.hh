#pragma once

#include <string>

#include "Component.hh"
#include "../GameTime.hh"

class Script : public Component, public ShouldUpdate
{
public:
    virtual const std::string Name();

    Script();
    ~Script();

    virtual void Start() = 0;
    virtual void Update(GameTime*) = 0;
};