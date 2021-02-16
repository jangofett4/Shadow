#include <iostream>

#include "Components/UI/UIBox.hh"

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
    auto shaderText = game->Assets->LoadShader("assets/shaders/text");
    
    auto model = game->Assets->LoadObjMesh("assets/bunny.obj");
    auto texture = game->Assets->LoadTexture("assets/textures/bunny-atlas.png");
    auto fontface = game->Assets->LoadFont("assets/fonts/fantasque-sans-mono-regular.ttf");

    if (!shaderUI || !shaderModel || !model || !texture || !fontface || !shaderText)
        return -1;

    auto font = fontface->LoadSize(14);

    if (shaderUI->DidError)
    {
        std::cout << shaderUI->GetError() << std::endl;
        return -1;
    }

    if (shaderText->DidError)
    {
        std::cout << shaderText->GetError() << std::endl;
        return -1;
    }

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
        mater->Value("diffuseColor", vec4(0.0f, 1.0f, 1.0f, 0.7f));

        auto box = new GameObject("Box");
        box->transform->Scale = vec3(200, 100, 1);
        box->transform->Position = vec3(100, 100, 0);
        box->transform->Rotation = vec3(45, 0, 0);
        box->AddComponent(mater);
        box->AddComponent(new UIBox(mater, font));
        scene->AddGameObject(box, scene->Layers.UI);
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