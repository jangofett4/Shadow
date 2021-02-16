#include <string>

#include "../../RenderContext.hh"
#include "../UIElement.hh"
#include "../Material.hh"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

class UIWindow : public UIElement
{
    GLuint vao_win, vao_handle, vbo_win, vbo_handle;

public:
    virtual const std::string Name();
    float width, height;

    UIWindow(Material*);

    // void Setup();
    void Render(RenderContext&);
};