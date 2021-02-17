#include "UIContainer.hh"
#include "UILayoutEngine.hh"

const std::string UIContainer::Name() { return "UI Stack"; }

UIContainer::UIContainer()
{
    layoutEngine = new UILayoutEngine(this);
    // Layers.Background = layerManager.AddLayer("Background");
    // Layers.Default = layerManager.AddLayer("Default");
}

UIContainer::~UIContainer()
{
    // for (auto it = controls.begin(); it != controls.end(); it++)
    //     delete (*it);
    if (root)
        delete root;
    delete layoutEngine;
}

/*
void UIContainer::AddControl(UIControl* control, Layer<UIControl*>* layer)
{
    controls.push_back(control);
    if (layer == nullptr)
        layer = Layers.Default;
    layer->AddObject(control);
}
*/

void UIContainer::Setup() { }
void UIContainer::Render(RenderContext& context)
{
    if (!root)
        return;
    layoutEngine->Update(root); // Calculate bounds & positions
    root->Render(context);      // Root should handle rest
    // layerManager.RenderBackward(context);
}