#include "UIShader.hh"

const char* shader_src_ui_vs = R"glsl(
    #version 330 core
    layout(location = 0) in vec2 vsPosition;

    uniform mat4 modelViewProj;
    
    void main()
    {
        gl_Position = modelViewProj * vec4(vsPosition.xy, 1.0, 1.0);
    }
)glsl";

const char* shader_src_ui_fs = R"glsl(
    #version 330 core
    
    out vec4 outColor;
    uniform vec4 color;

    void main()
    {
        outColor = color;
    }
)glsl";

Shaders::UIShader::UIShader() : Shader(shader_src_ui_vs, shader_src_ui_fs) { }