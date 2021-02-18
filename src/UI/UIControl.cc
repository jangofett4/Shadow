#include "UIControl.hh"

UIEvents::UIEvents()
    :   MouseHoverEvent(),
        MouseExitEvent(),
        MouseClickEvent(),
        MouseLeftHoldEvent(),
        states()
{ }

void UIEvents::SetState(std::string state, bool value)
{
    states[state] = value;
}

bool UIEvents::GetState(std::string state)
{
    auto it = states.find(state);
    if (it == states.end())
        return false;
    return it->second;
}

UIControl::UIControl(float x, float y, float w, float h, Material* material, vec4 color, vec4 hover, vec4 click)
    :   position(x, y), size(w, h), margin(16.0f),
        anchor(AnchorMode::Normal), material(material),
        origPosition(position), origSize(size),
        color(color), origColor(color), hoverColor(hover), clickColor(click),
        parent(nullptr), controls(), events(new UIEvents())
{ }

UIControl::UIControl(vec2 position, vec2 size, Material* material, vec4 color, vec4 hover, vec4 click)
    :   position(position), size(size), margin(16.0f),
        anchor(AnchorMode::Normal), material(material),
        origPosition(position), origSize(size),
        color(color), origColor(color), hoverColor(hover), clickColor(click),
        parent(nullptr), controls(), events(new UIEvents())
{ }

UIControl::UIControl(vec4 pos_size, Material* material, vec4 color, vec4 hover, vec4 click)
    :   position(pos_size.x, pos_size.y), size(pos_size.z, pos_size.w), margin(16.0f),
        anchor(AnchorMode::Normal), material(material),
        origPosition(position), origSize(size), 
        color(color), origColor(color), hoverColor(hover), clickColor(click),
        parent(nullptr), controls(), events(new UIEvents())
{ }

UIControl::~UIControl()
{
    delete events;
}

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

vec4 UIControl::GetOriginalColor() { return origColor; }