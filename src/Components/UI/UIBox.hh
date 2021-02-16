#include <string>

#include "../../RenderContext.hh"
#include "../../Graphics/FontFace.hh"
#include "../UIElement.hh"
#include "../Material.hh"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

class UIBox : public UIElement
{
    GLuint vao, vbo;
    GlyphSet* font;
public:
    virtual const std::string Name();
    float width, height;

    UIBox(Material*, GlyphSet*);

    // void Setup();
    void Render(RenderContext&);
};