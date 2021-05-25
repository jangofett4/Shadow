#include "UIControl.hh"
#include "UIRoot.hh"

#include "../Input.hh"

UIEvents::UIEvents()
    :   MouseHoverEvent(),
        MouseExitEvent(),
        MouseClickEvent(),
        MouseLeftHoldEvent(),
        states()
{ }

void UIEvents::SetupKeyPressEvent(EventFunction<int32_t> evt)
{
    Input::Keyboard->InstallKeyPressTrigger(evt);
}

void UIEvents::SetupKeyReleaseEvent(EventFunction<int32_t> evt)
{
    Input::Keyboard->InstallKeyReleaseTrigger(evt);
}

void UIEvents::SetupTextEvent(EventFunction<uint32_t> evt)
{
    Input::Keyboard->InstallTextTrigger(evt);
}

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

UIControl::UIControl(float x, float y, float w, float h)
    :   position(x, y), size(w, h), margin(4.0f), padding(4.0f),
        anchor(AnchorMode::Default),
        parent(nullptr), events(new UIEvents()), focusable(false),
        isFocused(false), material(nullptr), cursor(CursorMode::Default), controls()
{
    origPosition = position;
    origSize = size;
}

UIControl::UIControl(vec2 position, vec2 size)
    :   position(position), size(size), margin(4.0f), padding(4.0f),
        anchor(AnchorMode::Default),
        parent(nullptr), events(new UIEvents()), focusable(false),
        isFocused(false), material(nullptr), cursor(CursorMode::Default), controls()
{
    origPosition = position;
    origSize = size;
}

UIControl::UIControl(vec4 pos_size)
    :   position(pos_size.x, pos_size.y), size(pos_size.z, pos_size.w), margin(4.0f), padding(4.0f),
        anchor(AnchorMode::Default),
        parent(nullptr), events(new UIEvents()), focusable(false),
        isFocused(false), material(nullptr), cursor(CursorMode::Default), controls()
{
    origPosition = position;
    origSize = size;
}

UIControl::~UIControl()
{
    delete events;
    for (auto it = controls.begin(); it != controls.end(); it++)
        delete *it;
}

vec2 UIControl::GetOriginalSize() { return origSize; }
vec2 UIControl::GetOriginalPosition() { return origPosition; }
/*
vec4 UIControl::GetOriginalColor() { return origColor; }
*/

vec2 UIControl::GetRelativePosition(vec2 abs) { return abs - position; }

void UIControl::AddControl(UIControl* control)
{
    control->parent = this;
    controls.push_back(control);
}

void UIControl::RemoveControl(UIControl* control)
{
    auto it = std::find(controls.begin(), controls.end(), control);
    if (it == controls.end()) return;
    control->parent = nullptr;
    controls.erase(it);
}

UIRoot* UIControl::GetRoot()
{
    if (!parent)
        return root;
    return parent->GetRoot();
}

UITheme* UIControl::GetTheme()
{
    return GetRoot()->Theme;
}

bool UIControl::IsFocused() { return isFocused; }

void UIControl::Render(RenderContext& context)
{
    for (auto it = controls.begin(); it != controls.end(); it++)
        (*it)->Render(context);
}

void UIControl::UpdateSelfLayout()
{
    auto newPosition = origPosition;
    auto newSize = origSize;

    if (!parent)
    {
        position = newPosition;
        size = newSize;
    }
    else
    {
        auto offset = parent->position;

        if (anchor & AnchorMode::Normal)
        {
            position = newPosition + offset + margin;
            size = newSize;
        }
        else
        {
            if (anchor & AnchorMode::Left)
            {
                newPosition.x = margin.x + parent->padding.x;
                if (anchor & AnchorMode::Right)
                    newSize.x = parent->size.x - (2 * margin.x) - (2 * parent->padding.x);
            }
            else if (anchor & AnchorMode::Right)
                newPosition.x = parent->size.x - margin.x - newSize.x - (2 * parent->padding.x);

            if (anchor & AnchorMode::Top)
            {
                newPosition.y = margin.y + parent->padding.y;
                if (anchor & AnchorMode::Bottom)
                    newSize.y = parent->size.y - (2 * margin.y) - (2 * parent->padding.y);
            }
            else if (anchor & AnchorMode::Bottom)
                newPosition.y = parent->size.y - margin.y - newSize.y - (2 * parent->padding.y);

            position = newPosition + offset;
            size = newSize;
        }
    }
}

void UIControl::UpdateChildLayout()
{
    for (auto it = controls.begin(); it != controls.end(); it++)
        (*it)->UpdateLayout();
}

void UIControl::UpdateLayout()
{
    UpdateSelfLayout();
    UpdateChildLayout();
}

/*
void UIControl::SetRoot(UIRoot* root)
{
    this->root = root;
}

void UIControl::ClearRoot()
{
    root = nullptr;
}
*/

/*
void UIControl::UpdateLayout(vec2 parentPosition, vec2 parentSize)
{
    // Dirty hack to force layout engine to use custom parent position
    // Actually is faster than calculating positions from scratch
    auto pos_save = parent->position;
    auto size_save = parent->size;
    parent->position = parentPosition;
    parent->size = parentSize;
    UpdateSelfLayout();
    parent->position = pos_save;
    parent->size = size_save;
}
*/

bool inbounds_2d(float x, float y, vec2 position, vec2 size)
{
    auto bounds = position + size;
    if (x > position.x && x < bounds.x && y > position.y && y < bounds.y)
        return true;
    return false;
}

void UIControl::ProcessEvents()
{
    auto mpX = Input::Mouse->GetMouseX();
    auto mpY = Input::Mouse->GetMouseY();
    auto mpClick = Input::Mouse->IsLMBClicked();    // Full click
    auto mpHold = Input::Mouse->IsLMBPressed();     // Press & hold
    auto rootobj = GetRoot();

    vec2 evposition(mpX, mpY);
    
    if (inbounds_2d(mpX, mpY, position, size))
    {
        CursorManager::SetCursor(cursor);
        events->SetState("inbound", true);
        events->MouseHoverEvent.CallAll(&evposition);
        if (mpHold)
            events->MouseLeftHoldEvent.CallAll(&evposition);
        if (mpClick)
        {
            if (focusable)
                rootobj->SetFocus(this);
            events->MouseClickEvent.CallAll(&evposition);
        }
    }
    else
    {
        // CursorManager::SetCursor(CursorMode::Default);
        if (events->GetState("inbound"))
        {
            events->SetState("inbound", false);
            events->MouseExitEvent.CallAll(&evposition);
        }
    }

    for (auto it = controls.begin(); it != controls.end(); it++)
        (*it)->ProcessEvents();
}