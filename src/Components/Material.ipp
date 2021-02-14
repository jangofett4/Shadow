#pragma once

#include "Material.hh"

template<typename T>
Uniform Uniform::Create(std::string name, UniformType type, GLint location, T value)
{
    Uniform uniform(name, type, location);
    uniform.value = value;
    return uniform;
}