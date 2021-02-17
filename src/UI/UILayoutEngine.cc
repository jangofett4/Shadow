#include "UILayoutEngine.hh"
#include "UIContainer.hh"

UILayoutEngine::UILayoutEngine(UIContainer* container) : container(container) { }

void UILayoutEngine::Update(UIControl* control)
{
    auto newPosition = control->GetOriginalPosition();
    auto newSize = control->GetOriginalSize();

    // No parent, absolute position & size
    if (!control->parent)
    {
        control->position = newPosition;    
        control->size = newSize;
    }
    else
    {
        auto offset = control->parent->position;

        if (control->anchor & AnchorMode::Normal)
        {
            // Just stick to original size & position, skip other calculations
            control->size = newSize;
            control->position = newPosition + offset + control->margin;
        }
        else
        {
            if (control->anchor & AnchorMode::Left)
            {
                newPosition.x = control->margin.x;
                if (control->anchor & AnchorMode::Right)
                    newSize.x = control->parent->size.x - (2 * control->margin.x);
            }
            else if (control->anchor & AnchorMode::Right)
                newPosition.x = control->parent->size.x - control->margin.x - newSize.x;

            if (control->anchor & AnchorMode::Top)
            {
                newPosition.y = control->margin.y;
                if (control->anchor & AnchorMode::Bottom)
                    newSize.y = control->parent->size.y - (2 * control->margin.y);
            }
            else if (control->anchor & AnchorMode::Bottom)
                newPosition.y = control->parent->size.y - control->margin.y - newSize.y;

            control->position = newPosition + offset;
            control->size = newSize;
        }
    }

    for (auto it = control->controls.begin(); it != control->controls.end(); it++)
        Update(*it);
}