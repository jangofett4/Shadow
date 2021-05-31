#include "UIRoot.hh"

const std::string UIRoot::Name() { return "UI Root Node"; }

UIRoot::UIRoot() : root(nullptr), Theme(MaterialDefaultTheme()), layerManager()
{
    Layers.Default = layerManager.AddLayer("Default");
    Layers.Popup = layerManager.AddLayer("Popup");
}

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
    control->layer = Layers.Default;
    root = control;
}

void UIRoot::Start()
{
    if (root)
    {
        // Controls can still operate without their root not being assigned
        // This is a measure I've taken to relieve some CPU cycles via not searching for root in parents
        // Reduces call count by A LOT
        root->InheritRoot();
        root->SetLayer(Layers.Default);
        root->Start();
    }
}

void UIRoot::Setup() { } // Residue of Renderer::Setup pure virtual function

void UIRoot::Update(GameTime* time)
{
    if (!root)
        return;
    root->UpdateLayout();
    root->ProcessEvents();
}

void UIRoot::Render(RenderContext& context)
{
    if (!root)
        return;
    
    layerManager.RenderForward(context, [](UIControl* control){ return control->visible; });
    //root->Render(context);      // Root should handle rest
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