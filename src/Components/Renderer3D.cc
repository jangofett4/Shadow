#include "Renderer3D.hh"
#include "../Helper/Mesh.hh"
#include "../GameObject.hh"

#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

const std::string Renderer3D::Name() { return "3D Renderer"; }

Renderer3D::Renderer3D(Material* mat) : material(mat) { }

Renderer3D::~Renderer3D() { }

void Renderer3D::Setup()
{
    // TODO: this is dumb, assigning the material twice (in constructor, in here)
    material = Parent->GetComponent<Material>();
    if (!material)
    {
        std::cout << "[Renderer3D] Error: No materials assigned for gameobject, skipping rendering for this gameobject." << std::endl;
        return;
    }
    gotransform = Parent->transform;
}

void Renderer3D::SetMesh(Mesh* mesh)
{
    // TODO: maybe move all values to function, they are useless as class members anyways
    
    model = mesh;
    // Create VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create Vertex VBO
    glGenBuffers(1, &vbo_vertex);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex);
    glBufferData(GL_ARRAY_BUFFER, mesh->Vertices.size() * sizeof(vec3), &mesh->Vertices[0], GL_STATIC_DRAW);
    /* Position */ glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0); glEnableVertexAttribArray(0);

    // Create UV VBO
    glGenBuffers(1, &vbo_uv);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
    glBufferData(GL_ARRAY_BUFFER, mesh->UVs.size() * sizeof(vec2), &mesh->UVs[0], GL_STATIC_DRAW);
    /* UV       */ glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0); glEnableVertexAttribArray(1);

    GLuint vbo_normal;
    glGenBuffers(1, &vbo_normal);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
    glBufferData(GL_ARRAY_BUFFER, mesh->Normals.size() * sizeof(vec3), &mesh->Normals[0], GL_STATIC_DRAW);
    /* Normal   */ glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0); glEnableVertexAttribArray(2);

    /*
    // Create EBO
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->Indices.size() * sizeof(GLuint), mesh->Indices.data(), GL_STATIC_DRAW);
    */
}

void Renderer3D::Render(RenderContext& context)
{
    if (!material || !model)
        return; // skip drawing, no material

    material->Value("modelViewProj", context.ModelViewProjection3D(gotransform));
    context.SetupTriple(material, vao);
    context.RenderArrays(model->Vertices.size());
}