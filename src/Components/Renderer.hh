#pragma once

#include <glm/glm.hpp>

#include "../RenderContext.hh"
#include "Component.hh"

using namespace glm;

class GameObject;

class Renderer : public Component
{
public:
    virtual const std::string Name() = 0;

    virtual ~Renderer();
    
    virtual void Setup() = 0;
    virtual void Render(const RenderContext&) = 0;
};