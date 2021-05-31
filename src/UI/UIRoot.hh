#pragma once

#include <vector>

#include "UIControl.hh"
#include "UITheme.hh"
#include "../RenderContext.hh"
#include "../Components/Renderer.hh"
#include "../LayerManager.hh"

/* This is UI root component
 * It's responsible to mainly render all controls in it.
 * It also keeps record of which controls are currently in focus,
 *  Which objects need focus removing and focus based events
 */
class UIRoot : public Renderer, public ShouldUpdate
{
    UIControl* root;
    std::vector<UIControl*> focused;
    LayerManager<UIControl*> layerManager;

public:
    struct {
        Layer<UIControl*>* Default;
        Layer<UIControl*>* Popup;
    } Layers;

    virtual const std::string Name();
    UITheme* Theme;

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