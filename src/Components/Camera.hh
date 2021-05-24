#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

#include "Component.hh"

using namespace glm;

class Camera : public Component
{
    vec3 transformedDirection;
public:
    float NearClippingPlane;
    float FarClippingPlane;
    float FOV;

    virtual const std::string Name();

    Camera(float, float, float);
    virtual ~Camera();
};