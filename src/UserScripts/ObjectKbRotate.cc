class RotScript : public Script
{
    void Start()
    {
    }

    void Update(GameTime* time)
    {
        Parent->transform->Rotation += vec3(0, 180, 0) * time->Delta;
    }
};