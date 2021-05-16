#pragma once

#include "../RenderContext.hh"
#include "../LayerManager.hh"
#include "../CallbackStack.hh"
#include "../Helper/CursorManager.hh"

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

template<typename T>
using EventFunction = std::function<void(T*)>;

class UIEvents
{
    std::unordered_map<std::string, bool> states;

public:
    UIEvents();
    
    CallbackStack<vec2> MouseHoverEvent;
    CallbackStack<vec2> MouseExitEvent;

    CallbackStack<vec2> MouseClickEvent;
    CallbackStack<vec2> MouseLeftHoldEvent;

    void SetupKeyPressEvent(EventFunction<int32_t> evt);
    void SetupKeyReleaseEvent(EventFunction<int32_t> evt);

    void SetupTextEvent(EventFunction<uint32_t> evt);

    bool GetState(std::string state);
    void SetState(std::string state, bool value);
};

class UIRoot;

class UIControl
{
    friend class UIRoot;
    
    vec4 origColor;             /* Original color of the control.                               */
    vec2 origSize;              /* Original size                                                */
    vec2 origPosition;          /* Original position                                            */

    bool isFocused;             /* Is this control in focus now?                                */

public:
    vec2 position;              /* Position of the element relative to container top-left       */
    vec2 size;                  /* Size of the element, double axis anchoring will edit this    */
    vec2 margin;                /* Margin from container                                        */
    vec2 padding;               /* Padding for elements inside this control                     */
    
    vec4 color;                 /* Color of the control                                         */
    vec4 hoverColor;            /* Hover color of the control                                   */
    vec4 clickColor;            /* Click color of the control                                   */

    uint32_t cursor;            /* Cursor style when this control is hovered over with mouse.   */

    uint32_t anchor;            /* Anchoring properties, used by layout engine                  */
    UIControl* parent;          /* Parent control of this control                               */
    UIEvents* events;           /* Event list for this control                                  */
    
    // Layer<UIControl*>* layer;/* UI layer that this control resides in                        */
    // Controls that are contained within this control
    // std::vector<UIControl*> controls;

    Material* material;         /* Material to render this control.                             */
                                /* If nullptr, RenderContext will assign a default one.         */
    bool focusable;             /* Is this control focusable? (spoilers, most of them are not)  */
    UIRoot* root;               /* Root of this control. Also root for children too.            */
    
    UIControl(float x, float y, float w, float h, vec4 color);
    UIControl(vec2 position, vec2 size, vec4 color);
    UIControl(vec4 pos_size, vec4 color);

    virtual ~UIControl();
    
    vec2 GetOriginalSize();
    vec2 GetOriginalPosition();

    vec4 GetOriginalColor();

    vec2 GetRelativePosition(vec2 abs);

    bool IsFocused();
    
    // Default layout engine, uses parent bounds if possible
    virtual void UpdateLayout();

    // Default layout engine, custom parent bounds are supplied
    virtual void UpdateLayout(vec2 parentPos, vec2 parentSize);

    virtual void ProcessEvents();

    virtual void Render(RenderContext& context) = 0;

    virtual void SetRoot(UIRoot* root);
    virtual void ClearRoot();
};