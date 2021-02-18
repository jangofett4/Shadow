#include "UIRoot.hh"

const std::string UIRoot::Name() { return "UI Stack"; }

UIRoot::UIRoot() { }

UIRoot::~UIRoot()
{
    if (root)
        delete root;
}

void UIRoot::Start() { } // Residue of ShouldUpdate::Start pure virtual function
void UIRoot::Setup() { } // Residue of Renderer::Setup pure virtual function

void UIRoot::Update(GameTime* time)
{
    if (root)
        root->ProcessEvents();
}

void UIRoot::Render(RenderContext& context)
{
    if (!root)
        return;
    root->UpdateLayout();   // Update control layout
    root->Render(context);  // Root should handle rest
    // layerManager.RenderBackward(context);
}