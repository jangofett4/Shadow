#include "UIContainer.hh"
#include "UILayoutEngine.hh"
#include "UIEventManager.hh"

const std::string UIContainer::Name() { return "UI Stack"; }

UIContainer::UIContainer()
{
    layoutEngine = new UILayoutEngine(this);
    eventManager = new UIEventManager(this);
}

UIContainer::~UIContainer()
{
    if (root)
        delete root;
    delete layoutEngine;
    delete eventManager;
}

void UIContainer::Start()
{
}

void UIContainer::Update(GameTime* time)
{
    if (root)
        eventManager->PushEvents(root);
}

void UIContainer::Setup() { }
void UIContainer::Render(RenderContext& context)
{
    if (!root)
        return;
    layoutEngine->Update(root); // Calculate bounds & positions
    root->Render(context);      // Root should handle rest
    // layerManager.RenderBackward(context);
}