#pragma once

#include <vector>

#include "UIControl.hh"
#include "../RenderContext.hh"
#include "../Components/Renderer.hh"

/* This is UI root component
 * It's responsible to mainly render all controls in it.
 * It also keeps record of which controls are currently in focus,
 *  Which objects need focus removing and focus based events
 */
class UIRoot : public Renderer, public ShouldUpdate
{
    UIControl* root;
    std::vector<UIControl*> focused;

public:
    virtual const std::string Name();

    UIRoot();
    virtual ~UIRoot();

    virtual void Start();
    virtual void Update(GameTime* time);

    void SetRoot(UIControl* control);
    
    virtual void Setup();
    virtual void Render(RenderContext& context);

    virtual void AddFocus(UIControl* control);
    virtual void SetFocus(UIControl* control);
    virtual void ClearFocus();
};