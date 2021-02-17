#include "UIControl.hh"

UIControl::UIControl(float x, float y, float w, float h, Material* material)
    :   position(x, y), size(w, h), margin(16.0f),
        anchor(AnchorMode::Normal), material(material),
        origPosition(position), origSize(size),
        parent(nullptr), controls()
{ }

UIControl::UIControl(vec2 position, vec2 size, Material* material)
    :   position(position), size(size), margin(16.0f),
        anchor(AnchorMode::Normal), material(material),
        origPosition(position), origSize(size),
        parent(nullptr), controls()
{ }

UIControl::UIControl(vec4 pos_size, Material* material)
    :   position(pos_size.x, pos_size.y), size(pos_size.z, pos_size.w), margin(16.0f),
        anchor(AnchorMode::Normal), material(material),
        origPosition(position), origSize(size), 
        parent(nullptr), controls()
{ }

void UIControl::AddControl(UIControl* control)
{
    control->parent = this;
    controls.push_back(control);
}

void UIControl::RemoveControl(UIControl* control)
{
    control->parent = nullptr;
    controls.erase(std::find(controls.begin(), controls.end(), control));
}

vec2 UIControl::GetOriginalSize() { return origSize; }
vec2 UIControl::GetOriginalPosition() { return origPosition; }