#pragma once

#include "../RenderContext.hh"
#include "../LayerManager.hh"
#include "../CallbackStack.hh"

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

class UIEvents
{
    std::unordered_map<std::string, bool> states;

public:
    UIEvents();
    
    CallbackStack<vec2> MouseHoverEvent;
    CallbackStack<vec2> MouseExitEvent;

    CallbackStack<vec2> MouseClickEvent;
    CallbackStack<vec2> MouseLeftHoldEvent;

    bool GetState(std::string state);
    void SetState(std::string state, bool value);
};

class UIControl
{
    // Original color of the control
    vec4 origColor;

    vec2 origSize;              /* Original size                                                */
    vec2 origPosition;          /* Original position                                            */
public:
    vec2 position;              /* Position of the element relative to container top-left       */
    vec2 size;                  /* Size of the element, double axis anchoring will edit this    */
    vec2 margin;                /* Margin from container                                        */
    
    vec4 color;                 /* Color of the control                                         */
    vec4 hoverColor;            /* Hover color of the control                                   */
    vec4 clickColor;            /* Click color of the control                                   */

    uint32_t anchor;            /* Anchoring properties, used by layout engine                  */
    Material* material;         /* Material used for rendering this control                     */
    // Layer<UIControl*>* layer;/* UI layer that this control resides in                        */
    UIControl* parent;          /* Parent control of this control                               */
    UIEvents* events;           /* Event list for this control                                  */
    // Controls that are contained within this control
    std::vector<UIControl*> controls;
    
    UIControl(float x, float y, float w, float h, Material* material, vec4 color, vec4 hover, vec4 click);
    UIControl(vec2 position, vec2 size, Material* material, vec4 color, vec4 hover, vec4 click);
    UIControl(vec4 pos_size, Material* material, vec4 color, vec4 hover, vec4 click);

    ~UIControl();

    void AddControl(UIControl* control);
    void RemoveControl(UIControl* control);
    
    vec2 GetOriginalSize();
    vec2 GetOriginalPosition();

    vec4 GetOriginalColor();

    virtual void Render(RenderContext& context) = 0;
};