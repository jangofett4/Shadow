#include <iostream>

#include "UI/UIRoot.hh"
#include "UI/Controls/UIWindow.hh"
#include "UI/Controls/UIStack.hh"
#include "UI/Controls/UIGroupBox.hh"
#include "UI/Controls/UILabel.hh"
#include "UI/Controls/UISplitHorizontal.hh"
#include "UI/Controls/UISplitVertical.hh"
#include "UI/Controls/UIButton.hh"
#include "UI/Controls/UITextBox.hh"
#include "UI/Controls/UIToggleButton.hh"
#include "UI/Controls/UISlider.hh"
#include "UI/Controls/UIProgressBar.hh"
#include "UI/Controls/UIListBox.hh"
#include "UI/Controls/UIBarGraph.hh"
#include "UI/Controls/UIComboBox.hh"

#include "Components.hh"
#include "Game.hh"

/*
#include "UserScripts/ObjectKbRotate.cc"
#include "UserScripts/CameraFreeLook.cc"
*/

#define Width   600
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


    auto bunny = game->Assets->LoadObjMesh("assets/bunny.obj");
    auto fontface = game->Assets->LoadFont("assets/fonts/fantasque-sans-mono-regular.ttf");
    auto base = game->Assets->LoadShader("assets/shaders/base");

    if (!fontface || !base || !bunny)
        return -1;

    auto font = fontface->LoadSize(14);
    
    {
        auto uiobj = new GameObject("ui");
        auto uiroot = new UIRoot(); 
        auto window = new UIWindow(vec2(0, 0), vec2(600, 400));
        auto split = new UISplitVertical();
        window->AddControl(split);

        auto group_left = new UIGroupBox(L"Left Group Box", font);
        auto stack_left = new UIStack();
        group_left->AddControl(stack_left);
        split->AddControl(group_left, VerticalSplitSide::Left);

        stack_left->AddControl(new UILabel("Enter Text:", vec2(), font));
        stack_left->AddControl(new UITextBox(vec2(), vec2(24), font));
        auto toggle1 = new UIToggleButton("State: false", vec2(), vec2(24), font);
        auto toggle2 = new UIToggleButton("State: false", vec2(), vec2(24), font);
        toggle1->_events.OnStateChange([toggle1](bool* state){
            auto status = std::string(*state ? "true" : "false");
            toggle1->label = "State: " + status;
        });
        stack_left->AddControl(toggle1);
        stack_left->AddControl(toggle2);
        auto list = new UIListBox<int>(vec2(), vec2(50), font);
        list->AddItem(L"Item 1", 1);
        list->AddItem(L"Item 2", 2);
        list->AddItem(L"Item 3", 3);
        stack_left->AddControl(list);

        auto slider = new UISlider(vec2(), 0);
        auto progress = new UIProgressBar(vec2(), 0);
        stack_left->AddControl(slider);
        stack_left->AddControl(progress);

        slider->_events.OnChangeEvent([&](int* state){
            progress->SetProgress(*state);
        });

        auto split_hor = new UISplitHorizontal();
        split->AddControl(split_hor, VerticalSplitSide::Right);
        auto group_r_top = new UIGroupBox(L"Right Top", font), group_r_bottom = new UIGroupBox(L"Right Bottom", font);
        split_hor->AddControl(group_r_top, HorizontalSplitSide::Top);
        split_hor->AddControl(group_r_bottom, HorizontalSplitSide::Bottom);

        auto combo = new UIComboBox<int>(vec2(), vec2(24), font);
        group_r_top->AddControl(combo);
        combo->AddItem(L"First Data", 10.0f);
        combo->AddItem(L"Second Data", 20.0f);
        combo->AddItem(L"Third Data", 30.0f);

        uiroot->SetRoot(window);
        uiobj->AddComponent(uiroot);
        scene->AddGameObject(uiobj);
    }
    

    /* extreme load test */
    /*
    {
        for (size_t i = 0; i < 5000; i++)
        {
            auto go = new GameObject(("bunny" + std::to_string(i)).c_str());
            go->transform->Scale = vec3(.1f, .1f, .1f);
            auto mat = new Material(base);
            mat->Value("diffuseColor", vec4(0, 0, 0, 255));
            auto renderer3d = new Renderer3D(mat);
            renderer3d->SetMesh(bunny);
            go->AddComponent(mat);
            go->AddComponent(renderer3d);
            scene->AddGameObject(go);
        }
    }
    */

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