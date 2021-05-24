#include "TextShader.hh"

const char* shader_src_text_vs = R"glsl(
    #version 330 core
    layout(location = 0) in vec2 vsPosition;
    layout(location = 1) in vec2 vsUV;

    out vec2 fsUV;

    uniform mat4 modelViewProj;

    void main()
    {
        fsUV = vsUV;
        gl_Position =  modelViewProj * vec4(vsPosition, 1.0, 1.0);
    }
)glsl";

const char* shader_src_text_fs = R"glsl(
    #version 330 core
    in vec2 fsUV;
    out vec4 outColor;

    uniform sampler2D fsCharTexture;
    uniform vec4 fsTextColor;

    void main()
    {
        float texVal = texture(fsCharTexture, fsUV).r;
        if (texVal == 0)
            discard;
        outColor = fsTextColor * vec4(1.0, 1.0, 1.0, texture(fsCharTexture, fsUV).r);
    }  
)glsl";

Shaders::TextShader::TextShader() : Shader(shader_src_text_vs, shader_src_text_fs) { }