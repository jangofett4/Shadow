#include <iostream>

#include "UI/UIRoot.hh"
#include "UI/Controls/UIWindow.hh"
#include "UI/Controls/UIStack.hh"
#include "UI/Controls/UISplitHorizontal.hh"
#include "UI/Controls/UISplitVertical.hh"
#include "UI/Controls/UIButton.hh"

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

    auto shaderModel = game->Assets->LoadShader("assets/shaders/base");
    auto shaderUI = game->Assets->LoadShader("assets/shaders/ui");
    // auto shaderText = game->Assets->LoadShader("assets/shaders/text");
    
    auto model = game->Assets->LoadObjMesh("assets/bunny.obj");
    auto texture = game->Assets->LoadTexture("assets/textures/bunny-atlas.png");
    auto fontface = game->Assets->LoadFont("assets/fonts/fantasque-sans-mono-regular.ttf");

    if (!shaderUI || !shaderModel || !model || !texture || !fontface /*|| !shaderText */)
        return -1;

    auto font = fontface->LoadSize(14);

    if (shaderUI->DidError)
    {
        std::cout << shaderUI->GetError() << std::endl;
        return -1;
    }

    /*
    if (shaderText->DidError)
    {
        std::cout << shaderText->GetError() << std::endl;
        return -1;
    }
    */

    {
        auto mat = new Material(shaderModel);
        mat->Value("diffuseColor", vec4(1.0f, 1.0f, 1.0f, 1.0f));
        mat->Value("albedo", texture);

        auto go = new GameObject("Bunny");
        go->transform->Rotation.y = -90;
        go->AddComponent(mat);
        go->AddComponent(new RotScript());
        auto renderer = new Renderer3D(mat);
        renderer->SetMesh(model);
        go->AddComponent(renderer);
        go->transform->Scale = vec3(0.1, 0.1, 0.1);
        scene->AddGameObject(go);
    }

    {
        auto mater = new Material(shaderUI);
        auto go = new GameObject("container");
        auto container = new UIRoot();
        auto win = new UIWindow(vec2(100, 100), vec2(300, 450));
        auto splith = new UISplitHorizontal();
        auto splitv = new UISplitVertical();
        auto stack1 = new UIStack();
        auto stack2 = new UIStack();
        auto stack3 = new UIStack();
        for (size_t i = 0; i < 3; i++)
            stack1->AddControl(new UIButton("Br", vec2(), vec2(0, 25), font));
        for (size_t i = 0; i < 3; i++)
            stack2->AddControl(new UIButton("uh", vec2(), vec2(0, 25), font));
        for (size_t i = 0; i < 3; i++)
            stack3->AddControl(new UIButton("Moment" + std::to_string(i), vec2(), vec2(0, 25), font));
        splitv->AddControl(stack1, VerticalSplitSide::Left);
        splitv->AddControl(stack2, VerticalSplitSide::Right);
        splith->AddControl(splitv, HorizontalSplitSide::Top);
        splith->AddControl(stack3, HorizontalSplitSide::Bottom);
        win->AddControl(splith);
        // bg->color = vec4(1, 0, 0.4, 0.8);
        container->root = win;
        go->AddComponent(container);
        scene->AddGameObject(go);
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