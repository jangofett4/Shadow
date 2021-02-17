#include <iostream>

#include "UI/UIContainer.hh"
#include "UI/Controls/UIWindow.hh"
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
        auto container = new UIContainer();
        auto win = new UIWindow(vec2(100, 100), vec2(300, 450), mater);
        auto btn = new UIButton("Bruh Button", vec2(0, 16), vec2(0, 25), mater, font);
        win->AddControl(btn);
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