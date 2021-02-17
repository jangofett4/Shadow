#pragma once

#include "../RenderContext.hh"
#include "../LayerManager.hh"

#include <glm/glm.hpp>

using namespace glm;

struct AnchorMode
{
    enum : uint32_t
    {
        Normal  = 1 << 1,
        Top     = 1 << 2,
        Bottom  = 1 << 3,
        Left    = 1 << 4,
        Right   = 1 << 5,
    };
};

class UIControl
{
    vec2 origSize;              /* Original size                                                */
    vec2 origPosition;          /* Original position                                            */
public:
    vec2 position;              /* Position of the element relative to container top-left       */
    vec2 size;                  /* Size of the element, double axis anchoring will edit this    */
    vec2 margin;                /* Margin from container                                        */
    uint32_t anchor;            /* Anchoring properties, used by layout engine                  */
    Material* material;         /* Material used for rendering this control                     */
    // Layer<UIControl*>* layer;/* UI layer that this control resides in                        */
    UIControl* parent;          /* Parent control of this control                               */
    // Controls that are contained within this control
    std::vector<UIControl*> controls;
    
    UIControl(float x, float y, float w, float h, Material* material);
    UIControl(vec2 position, vec2 size, Material* material);
    UIControl(vec4 pos_size, Material* material);

    void AddControl(UIControl* control);
    void RemoveControl(UIControl* control);
    
    vec2 GetOriginalSize();
    vec2 GetOriginalPosition();

    virtual void Render(RenderContext& context) = 0;
};