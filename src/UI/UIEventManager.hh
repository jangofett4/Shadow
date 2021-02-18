#pragma once

#include "UIContainer.hh"

class UIEventManager
{
    UIContainer* parent;
public:
    UIEventManager(UIContainer* parent);

    void PushEvents(UIControl* control);
    bool InBounds(float x, float y, vec2 position, vec2 size);
};