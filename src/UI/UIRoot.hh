#pragma once

#include <vector>

#include "UIControl.hh"
#include "../RenderContext.hh"
#include "../Components/Renderer.hh"

class UIRoot : public Renderer, public ShouldUpdate
{
public:
    virtual const std::string Name();
    UIControl* root;

    UIRoot();
    virtual ~UIRoot();

    virtual void Start();
    virtual void Update(GameTime* time);

    virtual void Setup();
    virtual void Render(RenderContext& context);
};