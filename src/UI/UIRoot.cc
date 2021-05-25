#include "UIRoot.hh"

const std::string UIRoot::Name() { return "UI Root Node"; }

UIRoot::UIRoot() : root(nullptr), Theme(MaterialDefaultTheme()) { }

UIRoot::~UIRoot()
{
    if (root)
        delete root;
}

void UIRoot::SetRoot(UIControl* control)
{
    if (root)
        root->root = nullptr;
    control->root = this;
    root = control;
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
    root->UpdateLayout();       // Update control layout
    root->Render(context);      // Root should handle rest
    // layerManager.RenderBackward(context);
}

void UIRoot::AddFocus(UIControl* control)
{
    control->isFocused = true;
    focused.push_back(control);
}

void UIRoot::SetFocus(UIControl* control)
{
    ClearFocus();
    control->isFocused = true;
    focused.push_back(control);
}

void UIRoot::ClearFocus()
{
    for (auto it = focused.begin(); it != focused.end(); it++)
        (*it)->isFocused = false;
    focused.clear();
}