class FreeLook : public Script
{
public:
    float MoveSpeed = 10;
    float RotationSpeed = 10;

    bool EnableZoom = true;
    float ZoomSpeed = 50;
    Camera* cam;

    void Start()
    {
        cam = Parent->GetComponent<Camera>();
    }

    void Update(GameTime* time)
    {
        if (!cam)
            return;
        auto dir = Parent->transform->Forward();
        auto motionY = Input::Mouse->GetMouseMotionY();
        auto motionX = Input::Mouse->GetMouseMotionX();
        std::cout << "X: " << motionX << ", Y : " << motionY << std::endl;
        std::cout << "X: " << Input::Mouse->GetMouseX() << ", Y : " << Input::Mouse->GetMouseY() << std::endl;
        auto rotVec = vec3(
            motionY,
            -motionX,
            0.0f
        );
        auto offset = glm::normalize(dir) * (Input::Keyboard->IsPressed(GLFW_KEY_W) ? 1.0f : Input::Keyboard->IsPressed(GLFW_KEY_S) ? -1.0f : 0.0f) * MoveSpeed * time->Delta;
        Parent->transform->Position += offset;
        Parent->transform->Rotation += rotVec * RotationSpeed * time->Delta;
        if (EnableZoom)
            cam->FOV -= Input::Mouse->GetMouseScrollY() * ZoomSpeed * time->Delta;
    }
};