#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Transform.hh"

const vec3 Transform::VecForward = vec3(0.f, 0.f, 1.f);

const std::string Transform::Name() { return "Transform"; }

Transform::Transform() : Position(), Rotation(), Scale(1) { }
Transform::Transform(vec3 pos, vec3 rot, vec3 scale) : Position(pos), Rotation(rot), Scale(scale) { }

Transform::~Transform() { }

vec3 Transform::Forward()
{
    return quat(radians(Rotation)) * Transform::VecForward;
}