#pragma once

#include "Material.hh"

template<typename T>
Uniform* Uniform::Create(std::string name, UniformType type, GLint location, T value)
{
    auto uniform = new Uniform(name, type, location);
    uniform->value = value;
    return uniform;
}

/*
template<typename T>
bool Material::Apply(std::string name, T value)
{

}
*/