#include "UIEventManager.hh"
#include "../Input.hh"

#include <iostream>

UIEventManager::UIEventManager(UIContainer* parent) : parent(parent) { }

void UIEventManager::PushEvents(UIControl* control)
{
    auto mpX = Input::Mouse->GetMouseX();
    auto mpY = Input::Mouse->GetMouseY();
    auto mpClick = Input::Mouse->IsLMBClicked();    // Full click
    auto mpHold = Input::Mouse->IsLMBPressed();     // Press & hold

    vec2 position(mpX, mpY);
    
    if (InBounds(mpX, mpY, control->position, control->size))
    {
        control->events->SetState("inbound", true);
        control->events->MouseHoverEvent.CallAll(&position);
        if (mpHold)
            control->events->MouseLeftHoldEvent.CallAll(&position);
        if (mpClick)
            control->events->MouseClickEvent.CallAll(&position);
    }
    else
    {
        if (control->events->GetState("inbound"))
        {
            control->events->SetState("inbound", false);
            control->events->MouseExitEvent.CallAll(&position);
        }
    }

    for (auto it = control->controls.begin(); it != control->controls.end(); it++)
        PushEvents((*it));
}

bool UIEventManager::InBounds(float x, float y, vec2 position, vec2 size)
{
    auto bounds = position + size;
    if (x > position.x && x < bounds.x && y > position.y && y < bounds.y)
        return true;
    return false;
}