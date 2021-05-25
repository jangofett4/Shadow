#include <iostream>

#include "UI/UIRoot.hh"
#include "UI/Controls/UIWindow.hh"
#include "UI/Controls/UIStack.hh"
#include "UI/Controls/UILabel.hh"
#include "UI/Controls/UISplitHorizontal.hh"
#include "UI/Controls/UISplitVertical.hh"
#include "UI/Controls/UIButton.hh"
#include "UI/Controls/UITextBox.hh"
#include "UI/Controls/UIToggleButton.hh"
#include "UI/Controls/UISlider.hh"
#include "UI/Controls/UIProgressBar.hh"
#include "UI/Controls/UIListBox.hh"

#include "Components.hh"
#include "Game.hh"

/*
#include "UserScripts/ObjectKbRotate.cc"
#include "UserScripts/CameraFreeLook.cc"
*/

#define Width   300
#define Height  400

int main()
{
    auto game = new Game("UI Test", Width, Height);
    auto scene = new Scene();
    game->LoadScene(scene);

    /*
    auto shaderModel = game->Assets->LoadShader("assets/shaders/base");
    
    auto model = game->Assets->LoadObjMesh("assets/bunny.obj");
    auto texture = game->Assets->LoadTexture("assets/textures/bunny-atlas.png");
    */
   
    auto fontface = game->Assets->LoadFont("assets/fonts/fantasque-sans-mono-regular.ttf");
    auto wiggle = game->Assets->LoadShader("assets/shaders/ui", "assets/shaders/ui-wiggly");

    if (!fontface || !wiggle)
        return -1;

    auto font = fontface->LoadSize(14);

    {
        auto uiobj = new GameObject("ui");
        auto uiroot = new UIRoot();
        auto window = new UIWindow(vec2(50, 50), vec2(200, 300));
        window->anchor = AnchorMode::Left | AnchorMode::Right | AnchorMode::Top;

        {
            auto stack = new UIStack();
            auto label = new UILabel("Slider is: 0%", vec2(), font);
            auto slider = new UISlider(vec2(), 25);
            auto progress = new UIProgressBar(vec2(), 0);
            slider->_events.OnChangeEvent.Subscribe([label, progress](int* value) {
                label->label = "Slider is: " + std::to_string(*value) + "%";
                progress->SetProgress(*value);
            });
            stack->AddControl(slider);
            stack->AddControl(label);

            auto toggle1 = new UIToggleButton("State: false", vec2(), vec2(25), font);
            toggle1->_events.OnStateChange.Subscribe([toggle1](bool* state) {
                auto stateStr = std::string((*state) ? "true" : "false");
                toggle1->label = "State: " + stateStr;
            });
            auto toggle2 = new UIToggleButton("State: false", vec2(), vec2(25), font);
            toggle2->_events.OnStateChange.Subscribe([toggle2](bool* state) {
                auto stateStr = std::string((*state) ? "true" : "false");
                toggle2->label = "State: " + stateStr;
            });

            stack->AddControl(toggle1);
            stack->AddControl(toggle2);

            stack->AddControl(progress);

            auto textbox = new UITextBox(vec2(), vec2(25), font);
            auto additembutton = new UIButton("Add to List", vec2(), vec2(25), font);
            auto removeitembutton = new UIButton("Remove from List", vec2(), vec2(25), font);

            stack->AddControl(textbox);
            stack->AddControl(additembutton);
            stack->AddControl(removeitembutton);

            auto list = new UIListBox<std::wstring>(vec2(), vec2(0, 128), font);
            list->AddItem(L"List element 1");
            list->AddItem(L"List element 2");
            list->AddItem(L"List element 3");
            stack->AddControl(list);

            additembutton->events->MouseClickEvent.Subscribe([textbox, list](vec2*){
                list->AddItem(textbox->GetValue());
            });

            removeitembutton->events->MouseClickEvent.Subscribe([list](vec2*){
                auto selected = list->GetSelectedIndex();
                if (selected >= 0)
                    list->RemoveAt(selected);
            });

            window->AddControl(stack);
        }

        uiroot->SetRoot(window);
        uiobj->AddComponent(uiroot);
        scene->AddGameObject(uiobj);
    }

    {
        auto cam = new GameObject("Main Camera");
        cam->AddComponent(new Camera(0.1f, 1000.0f, 45.0f));
        cam->transform->Position = vec3(0, 0, -100);

        scene->AddGameObject(cam);
        scene->SetMainCamera("Main Camera");
    }

    game->Start();

    delete game;
    delete scene;
    return 0;
}