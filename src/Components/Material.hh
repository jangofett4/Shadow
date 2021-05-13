#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>

#include <glm/glm.hpp>

#include "Component.hh"
#include "../Graphics/Shader.hh"
#include "../Graphics/Texture.hh"

using namespace glm;

enum class UniformType
{
    Vec3, Vec4, Mat3, Mat4, Texture, Float, Double, Uint32, Int32
};

struct Uniform
{
    const std::string name;
    std::variant<
        vec3, vec4, mat3, mat4, Texture*,
        float, double, uint32_t, int32_t
    > value;
    UniformType type;
    GLint location;

    Uniform(std::string, UniformType, GLint);

    template<typename T>
    static Uniform* Create(std::string, UniformType, GLint, T);
};

class Material : public Component
{
    std::unordered_map<std::string, Uniform*> uniforms;

public:
    virtual const std::string Name();
    
    Shader* shader;

    Material(Shader*);
    ~Material();

    bool Value(std::string, vec3);
    bool Value(std::string, vec4);
    bool Value(std::string, mat3);
    bool Value(std::string, mat4);
    bool Value(std::string, Texture*);
    bool Value(std::string, float);
    bool Value(std::string, double);
    bool Value(std::string, uint32_t);
    bool Value(std::string, int32_t);

    GLuint GetProgram();
    Uniform* GetUniform(std::string name);

    void Apply();
    void ApplyUniform(Uniform* uniform);
};

#include "Material.ipp"