#pragma once

#include "UIControl.hh"

class UIContainer;

class UILayoutEngine
{
    UIContainer* container;
public:

    UILayoutEngine(UIContainer* container);

    void Update(UIControl* control);
};