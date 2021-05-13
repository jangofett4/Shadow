#include <iostream>

#include "UI/UIRoot.hh"
#include "UI/Controls/UIWindow.hh"
#include "UI/Controls/UIStack.hh"
#include "UI/Controls/UISplitHorizontal.hh"
#include "UI/Controls/UISplitVertical.hh"
#include "UI/Controls/UIButton.hh"
#include "UI/Controls/UIToggleButton.hh"
#include "UI/Controls/UISlider.hh"

#include "Components.hh"
#include "Game.hh"

#include "UserScripts/ObjectKbRotate.cc"
#include "UserScripts/CameraFreeLook.cc"

#define Width   1280
#define Height  720

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

    if (!fontface)
        return -1;

    auto font = fontface->LoadSize(14);

    {
        auto uiobj = new GameObject("ui");
        auto uiroot = new UIRoot();
        auto window = new UIWindow(vec2(50, 50), vec2(200, 300));
        window->anchor = AnchorMode::Left | AnchorMode::Right | AnchorMode::Top;
        uiroot->root = window;

        {
            auto stack = new UIStack();
            stack->AddControl(new UISlider(vec2(), 25));
            stack->AddControl(new UIButton("Test Button 0", vec2(), vec2(25), font));
            stack->AddControl(new UISlider(vec2(), 25));
            stack->AddControl(new UIButton("Test Button 0", vec2(), vec2(25), font));
            window->AddControl(stack);
        }

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