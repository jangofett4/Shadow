#pragma once

#include <string>

#include "../RenderContext.hh"
#include "Renderer.hh"
#include "Material.hh"
#include "Transform.hh"

class UIRenderer : public Renderer
{
    GLuint vao, vbo, ebo;

public:
    virtual const std::string Name();
    
    UIRenderer();
    ~UIRenderer();

    void Setup();
    void Render(RenderContext&);
};