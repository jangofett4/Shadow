#pragma once

#include <string>

#include "Renderer.hh"
#include "../RenderContext.hh"

class Renderer2D : public Renderer
{
public:
    virtual const std::string Name();

    Renderer2D();
    virtual ~Renderer2D();

    void Render(const RenderContext&);
};