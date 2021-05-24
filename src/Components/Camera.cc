#include "Camera.hh"
#include "../GameObject.hh"

const std::string Camera::Name() { return "Camera"; }

Camera::Camera(float near, float far, float fov) : NearClippingPlane(near), FarClippingPlane(far), FOV(fov)
{
    transformedDirection = vec3(1.f, 0.f, 0.f);
}

Camera::~Camera() { }