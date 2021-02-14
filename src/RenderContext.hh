#pragma once

#include <glm/glm.hpp>

using namespace glm;

struct RenderContext
{
    mat4 view;
    mat4 projection;
    mat4 screen;
    
    RenderContext(mat4, mat4, mat4);
};