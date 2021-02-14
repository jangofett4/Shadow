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
    /* Position */ material->shader->VertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

    // Create UV VBO
    glGenBuffers(1, &vbo_uv);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
    glBufferData(GL_ARRAY_BUFFER, mesh->UVs.size() * sizeof(vec2), &mesh->UVs[0], GL_STATIC_DRAW);
    /* UV       */ material->shader->VertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

    GLuint vbo_normal;
    glGenBuffers(1, &vbo_normal);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
    glBufferData(GL_ARRAY_BUFFER, mesh->Normals.size() * sizeof(vec3), &mesh->Normals[0], GL_STATIC_DRAW);
    /* Normal   */ material->shader->VertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);

    /*
    // Create EBO
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->Indices.size() * sizeof(GLuint), mesh->Indices.data(), GL_STATIC_DRAW);
    */
}

void Renderer3D::Render(const RenderContext& context)
{
    if (!material || !model)
        return; // skip drawing, no material
    
    glUseProgram(material->GetProgram());

    mat4 matModel(1.0f);
    matModel = glm::translate(matModel, gotransform->Position);
    matModel = glm::rotate(matModel, glm::radians(gotransform->Rotation.x), vec3(1.f, 0.f, 0.f));
    matModel = glm::rotate(matModel, glm::radians(gotransform->Rotation.y), vec3(0.f, 1.f, 0.f));
    matModel = glm::rotate(matModel, glm::radians(gotransform->Rotation.z), vec3(0.f, 0.f, 1.f));
    matModel = glm::scale(matModel, gotransform->Scale);

    auto mvp = context.projection * context.view * matModel;
    material->Value("modelViewProj", mvp);

    // Apply material settings
    material->Apply();

    glBindVertexArray(vao);
    // TODO: Use draw elements instead for probably better VRAM usage
    glDrawArrays(GL_TRIANGLES, 0, model->Vertices.size()); // TODO: check uint
}