#pragma once

#include <string>

#include "Renderer.hh"
#include "Material.hh"
#include "Transform.hh"
#include "../Helper/Mesh.hh"
#include "../RenderContext.hh"

class Renderer3D : public Renderer
{
    Mesh* model;
    Material* material;
    Transform* gotransform;
    GLuint vao, vbo_vertex, vbo_uv /*, ebo */;

public:
    virtual const std::string Name();

    Renderer3D(Material*);
    ~Renderer3D();

    void Setup();
    void Render(RenderContext&);

    void SetMesh(Mesh*);
};