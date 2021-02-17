#pragma once

#include <vector>

#include "UIControl.hh"
#include "../RenderContext.hh"
#include "../LayerManager.hh"
#include "../Components/Renderer.hh"

class UILayoutEngine;

class UIContainer : public Renderer
{
    friend class UILayoutEngine;
    UILayoutEngine* layoutEngine;

public:
    virtual const std::string Name();
    UIControl* root;

    UIContainer();
    virtual ~UIContainer();

    virtual void Setup();
    virtual void Render(RenderContext& context);
};

/*
class UIContainer : public Renderer
{
    friend class UILayoutEngine;

    std::vector<UIControl*> controls;
    LayerManager<UIControl*> layerManager;

    UILayoutEngine* layoutEngine;

public:
    vec2 size;
    vec2 position;

    struct {
        Layer<UIControl*>* Background;
        Layer<UIControl*>* Default;
    } Layers;

    virtual const std::string Name();

    UIContainer(vec2 position, vec2 size);
    virtual ~UIContainer();

    void AddControl(UIControl* control, Layer<UIControl*>* layer = nullptr);

    virtual void Setup();
    virtual void Render(RenderContext& context);
};
*/