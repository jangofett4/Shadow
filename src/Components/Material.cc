#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.hh"
#include "../Graphics/Texture.hh"

using namespace glm;

Uniform::Uniform(std::string name, UniformType type, GLint location) : name(name), type(type), location(location) { }

const std::string Material::Name() { return "Material"; }

Material::Material(Shader* program)
    : shader(program), uniforms()
{
}

Material::~Material()
{
    // OpenGL does reference counting on some types
    // No need to free uniforms
}

#define MaterialValueOverride(T, UT) bool Material::Value(std::string name, T value) { \
    auto u = uniforms.find(name); \
    if (u != uniforms.end()) \
        u->second->value = value; \
    else \
    { \
        auto program = shader->Program(); \
        auto uniform = glGetUniformLocation(program, name.c_str()); \
        if (uniform < 0) \
            return false; \
        uniforms.emplace(name, Uniform::Create(name, UniformType::UT, uniform, value)); \
        return true; \
    } \
    return true; \
}

MaterialValueOverride(vec3, Vec3)
MaterialValueOverride(vec4, Vec4)
MaterialValueOverride(mat3, Mat3)
MaterialValueOverride(mat4, Mat4)
MaterialValueOverride(float, Float)
MaterialValueOverride(double, Double)
MaterialValueOverride(uint32_t, Uint32)
MaterialValueOverride(int32_t, Int32)

bool Material::Value(std::string name, Texture* value)
{

    auto u = uniforms.find(name);
    if (u != uniforms.end())
        u->second->value = value;
    else
    {
        auto program = shader->Program();
        auto uniform = glGetUniformLocation(program, name.c_str());
        if (uniform < 0)
            return false;
        uniforms.emplace(name, Uniform::Create(name, UniformType::Texture, uniform, value));
        return true;
    }
    return true;
}

void Material::ApplyUniform(Uniform* uniform)
{
    switch(uniform->type)
    {
        case UniformType::Vec3:
            glUniform3fv(uniform->location, 1, value_ptr(std::get<vec3>(uniform->value)));
            break;
        case UniformType::Vec4:
            glUniform4fv(uniform->location, 1, value_ptr(std::get<vec4>(uniform->value)));
            break;
        case UniformType::Mat3:
            glUniformMatrix3fv(uniform->location, 1, false, value_ptr(std::get<mat3>(uniform->value)));
            break;
        case UniformType::Mat4:
            glUniformMatrix4fv(uniform->location, 1, false, value_ptr(std::get<mat4>(uniform->value)));
            break;
        case UniformType::Texture:
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, std::get<Texture*>(uniform->value)->GetTextureID());
            glUniform1i(uniform->location, 0);
            break;
        case UniformType::Float:
            glUniform1f(uniform->location, std::get<float>(uniform->value));
            break;
        case UniformType::Double:
            glUniform1d(uniform->location, std::get<double>(uniform->value));
            break;
        case UniformType::Uint32:
            glUniform1ui(uniform->location, std::get<uint32_t>(uniform->value));
            break;
        case UniformType::Int32:
            glUniform1i(uniform->location, std::get<int32_t>(uniform->value));
            break;
        default:
            break;
    }
}

void Material::Apply()
{
    for (auto it = uniforms.begin(); it != uniforms.end(); it++)
        ApplyUniform(it->second);
}

GLuint Material::GetProgram()
{
    return shader->Program();
}

Uniform* Material::GetUniform(std::string name)
{
    auto find = uniforms.find(name);
    if (find != uniforms.end())
        return find->second;
    return nullptr;
}