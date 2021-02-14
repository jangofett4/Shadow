#pragma once

#include <string>
#include <typeinfo>
#include <typeindex>

#include "Component.hh"
#include <glm/glm.hpp>

using namespace glm;

class Transform : public Component
{
public:
    static const vec3 VecForward;

    virtual const std::string Name();

    vec3 Position;
    vec3 Rotation; // TODO: maybe use quat
    vec3 Scale;

    Transform();
    Transform(vec3, vec3, vec3);

    ~Transform();

    vec3 Forward();
};