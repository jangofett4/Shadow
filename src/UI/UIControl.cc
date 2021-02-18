#include "UIControl.hh"

#include "../Input.hh"

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

UIControl::UIControl(float x, float y, float w, float h, vec4 color)
    :   position(x, y), size(w, h), margin(8.0f), padding(8.0f),
        anchor(AnchorMode::Normal),
        origPosition(position), origSize(size),
        color(color), origColor(color),
        parent(nullptr), events(new UIEvents())
{ }

UIControl::UIControl(vec2 position, vec2 size, vec4 color)
    :   position(position), size(size), margin(8.0f), padding(8.0f),
        anchor(AnchorMode::Normal),
        origPosition(position), origSize(size),
        color(color), origColor(color),
        parent(nullptr), events(new UIEvents())
{ }

UIControl::UIControl(vec4 pos_size, vec4 color)
    :   position(pos_size.x, pos_size.y), size(pos_size.z, pos_size.w), margin(8.0f), padding(8.0f),
        anchor(AnchorMode::Normal),
        origPosition(position), origSize(size), 
        color(color), origColor(color),
        parent(nullptr), events(new UIEvents())
{ }

UIControl::~UIControl()
{
    delete events;
}

vec2 UIControl::GetOriginalSize() { return origSize; }
vec2 UIControl::GetOriginalPosition() { return origPosition; }

vec4 UIControl::GetOriginalColor() { return origColor; }

void UIControl::UpdateLayout()
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

void UIControl::UpdateLayout(vec2 parentPosition, vec2 parentSize)
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
        auto offset = parentPosition;

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
                    newSize.x = parentSize.x - (2 * margin.x) - (2 * parent->padding.x);
            }
            else if (anchor & AnchorMode::Right)
                newPosition.x = parentSize.x - margin.x - newSize.x - (2 * parent->padding.x);

            if (anchor & AnchorMode::Top)
            {
                newPosition.y = margin.y + parent->padding.y;
                if (anchor & AnchorMode::Bottom)
                    newSize.y = parentSize.y - (2 * margin.y) - (2 * parent->padding.y);
            }
            else if (anchor & AnchorMode::Bottom)
                newPosition.y = parentSize.y - margin.y - newSize.y - (2 * parent->padding.y);

            position = newPosition + offset;
            size = newSize;
        }
    }
}

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

    vec2 evposition(mpX, mpY);
    
    if (inbounds_2d(mpX, mpY, position, size))
    {
        events->SetState("inbound", true);
        events->MouseHoverEvent.CallAll(&evposition);
        if (mpHold)
            events->MouseLeftHoldEvent.CallAll(&evposition);
        if (mpClick)
            events->MouseClickEvent.CallAll(&evposition);
    }
    else
    {
        if (events->GetState("inbound"))
        {
            events->SetState("inbound", false);
            events->MouseExitEvent.CallAll(&evposition);
        }
    }
}