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
        All     = Left | Right | Top | Bottom
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
    vec2 padding;               /* Padding for elements inside this control                     */
    
    vec4 color;                 /* Color of the control                                         */
    vec4 hoverColor;            /* Hover color of the control                                   */
    vec4 clickColor;            /* Click color of the control                                   */

    uint32_t anchor;            /* Anchoring properties, used by layout engine                  */
    // Layer<UIControl*>* layer;/* UI layer that this control resides in                        */
    UIControl* parent;          /* Parent control of this control                               */
    UIEvents* events;           /* Event list for this control                                  */
    // Controls that are contained within this control
    // std::vector<UIControl*> controls;
    
    UIControl(float x, float y, float w, float h, vec4 color);
    UIControl(vec2 position, vec2 size, vec4 color);
    UIControl(vec4 pos_size, vec4 color);

    ~UIControl();
    
    vec2 GetOriginalSize();
    vec2 GetOriginalPosition();

    vec4 GetOriginalColor();

    // Default layout engine, uses parent bounds if possible
    virtual void UpdateLayout();

    // Default layout engine, custom parent bounds are supplied
    virtual void UpdateLayout(vec2 parentPos, vec2 parentSize);

    virtual void ProcessEvents();

    virtual void Render(RenderContext& context) = 0;
};