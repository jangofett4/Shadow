#pragma once

#include <string>

#include "../RenderContext.hh"
#include "Renderer.hh"
#include "Material.hh"

class UIElement : public Renderer
{
    Material* material;
public:
    virtual const std::string Name() = 0;

    UIElement(Material*);
    virtual ~UIElement();

    virtual void Setup();
    Material* GetMaterial();

    void Render(const RenderContext&) = 0;
};