#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <thread>
#include <chrono>

#include "Game.hh"
#include "Scene.hh"
#include "GameObject.hh"
#include "GameTime.hh"
#include "RenderContext.hh"

using namespace glm;

Game::Game(const char* title, int width, int height)
    : width(width), height(height), GameMutex(new std::mutex()), Assets(new AssetManager())
{
    glewExperimental = true;

    if (!glfwInit())
    {
        ErrorString = "[ShadowCC] Unable to initiliaze GLFW3!";
        DidError = true;
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!Window)
    {
        ErrorString = "[ShadowCC] Unable to create window!";
        DidError = true;
        return;
    }

    glfwMakeContextCurrent(Window);
    glewExperimental = true; // TODOLP: check if this is really needed

    if (glewInit() != GLEW_OK)
    {
        ErrorString = "[ShadowCC] Unable to initialize GLEW!";
        DidError = true;
        return;
    }

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling for better performance
    glEnable(GL_CULL_FACE);

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    // Disable 4x. textures size requirement
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(
        Window,
        videoMode->width / 2 - (width / 2),
        videoMode->height / 2 - (height / 2)
    );

    // Initialize input
    Input::Cleanup();   // Release resources if someone is already initialized before
    Input::Init(this);

    DidError = false;
}

Game::~Game()
{
    glfwDestroyWindow(Window);
    
    // delete CurrentScene; // scene might be used in another game, dont delete it
    Input::Cleanup();
    delete GameMutex;
    delete Assets;
}

GLFWwindow* Game::GetWindow() const
{
    return Window;
}

std::string Game::GetError()
{
    return ErrorString;
}

void Game::LoadScene(Scene* scene)
{
    CurrentScene = scene;
    GameMutex->lock();
    Exit = true; 
    GameMutex->unlock();
}

void Game::Start()
{
    Exit = false;
    if (!CurrentScene)
    {
        ErrorString = "[Game] Error: No scene is open"; 
        std::cout << ErrorString << std::endl;
        DidError = true;
        return;
    }

    GameTime* time = new GameTime();
    typedef std::chrono::high_resolution_clock Time;

    time->Delta = 0;

    // Call 'Start' functions of some GameObjects
    CurrentScene->SceneStart();

    RenderContext ctx;
    while (!Exit)
    {
        auto start_time = Time::now();

        // Clear color & depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update Scene
        CurrentScene->SceneUpdate(time);

        auto cam = CurrentScene->GetMainCamera();
        if (!cam)
            continue;
        
        // Render Scene
        Transform* camTransform = cam->Parent->transform;
        auto dir = camTransform->Forward() + camTransform->Position;

        auto viewMat = glm::lookAt(
            camTransform->Position,
            dir,
            glm::vec3(0, 1, 0)
        );

        auto projMat = glm::perspective(glm::radians(cam->FOV), (float)width / height, cam->NearClippingPlane, cam->FarClippingPlane);
        auto screenProjMat = glm::ortho(0.0f, (float)width, (float)height, 0.0f);

        ctx.view = viewMat;
        ctx.projection = projMat;
        ctx.screen = screenProjMat;
        CurrentScene->SceneRender(ctx);

        // Present
        glfwSwapBuffers(Window);
        glfwPollEvents();

        if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            break;
            // Exit = true;

        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
        
        auto end_time = Time::now();
        
        time->FrameTime = end_time - start_time;
        time->Delta = std::chrono::duration_cast<std::chrono::milliseconds>(time->FrameTime).count() / 1000.0f;
        std::cout << "FrameTime: " << time->FrameTime.count() << ", Delta: " << time->Delta << std::endl;
    }

    delete time;
}

void Game::LockCursor()
{
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // TODO: this is a dumb way to fix mouse motion snapping that happens in the first frames
    // properly implement mouse input
    Input::Cleanup();
    Input::Init(this);
    // Input::Mouse->ResetTo(Input::Mouse->GetMouseX(), Input::Mouse->GetMouseY());
}

void Game::ReleaseCursor()
{
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}