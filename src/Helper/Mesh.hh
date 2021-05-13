#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

/*
struct Triangle
{
    vec3& v0, v1, v2;

    Triangle(vec3&, vec3&, vec3&);
};
*/

class Mesh
{
public:
    std::vector<vec3> Vertices;
    std::vector<vec3> Normals;
    std::vector<vec2> UVs;
    // std::vector<GLuint> Indices;

    Mesh();
};
