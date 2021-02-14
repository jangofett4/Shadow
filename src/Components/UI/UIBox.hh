#include <string>

#include "../../RenderContext.hh"
#include "../UIElement.hh"
#include "../Material.hh"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

class UIBox : public UIElement
{
    GLuint vao, vbo;

public:
    virtual const std::string Name();
    float width, height;

    UIBox(Material*);

    // void Setup();
    void Render(const RenderContext&);
};