#pragma once

#include <vector>

#include "UIControl.hh"
#include "../RenderContext.hh"
#include "../LayerManager.hh"
#include "../Components/Renderer.hh"

class UILayoutEngine;
class UIEventManager;

class UIContainer : public Renderer, public ShouldUpdate
{
    UILayoutEngine* layoutEngine;
    UIEventManager* eventManager;

public:
    virtual const std::string Name();
    UIControl* root;

    UIContainer();
    virtual ~UIContainer();

    virtual void Start();
    virtual void Update(GameTime* time);

    virtual void Setup();
    virtual void Render(RenderContext& context);
};