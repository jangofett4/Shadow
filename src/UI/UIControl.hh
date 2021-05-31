#pragma once

#include "UITheme.hh"
#include "../RenderContext.hh"
#include "../LayerManager.hh"
#include "../CallbackStack.hh"
#include "../Helper/CursorManager.hh"

#include <glm/glm.hpp>

using namespace glm;

extern CallbackStack<char> StaticHelper;

struct AnchorMode
{
    enum : uint32_t
    {
        Normal  = 1 << 1,                       // I cant remember
        Top     = 1 << 2,                       // Toward top of parent
        Bottom  = 1 << 3,                       // Toward bottom of parent
        Left    = 1 << 4,                       // Toward left or parent
        Right   = 1 << 5,                       // Toward right of parent
        Float   = 1 << 6,                       // Absolute position
        Default = Left | Right | Top,           // Default anchor for controls
        All     = Left | Right | Top | Bottom,  // All anchor, generally for containers
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

    bool isFocused;             /* Is this control in focus now?                                */

    vec2 origPosition, origSize;

    UIRoot* root;               /* Root of this control. Also root for children too.            */
    UIControl* parent;          /* Parent control of this control                               */
    
public:
    vec2 position;              /* Position of the element relative to container top-left       */
    vec2 size;                  /* Size of the element, double axis anchoring will edit this    */
    vec2 margin;                /* Margin from container                                        */
    vec2 padding;               /* Padding for elements inside this control                     */

    uint32_t cursor;            /* Cursor style when this control is hovered over with mouse.   */

    uint32_t anchor;            /* Anchoring properties, used by layout engine                  */
    UIEvents* events;           /* Event list for this control                                  */

    bool enabled;               /* Is this control enabled?                                     */
    bool visible;               /* Is this control visible?                                     */
    
    Layer<UIControl*>* layer;   /* UI layer that this control resides in                        */
    // Controls that are contained within this control
    // std::vector<UIControl*> controls;

    Material* material;         /* Material to render this control.                             */
                                /* If nullptr, RenderContext will assign a default one.         */
    bool focusable;             /* Is this control focusable? (spoilers, most of them are not)  */

    // Children controls contained within this control
    std::vector<UIControl*> controls;

    UIControl(float x, float y, float w, float h);
    UIControl(vec2 position, vec2 size);
    UIControl(vec4 pos_size);

    virtual ~UIControl();
    
    vec2 GetOriginalSize();
    vec2 GetOriginalPosition();
    /*
    vec4 GetOriginalColor();
    */

    vec2 GetRelativePosition(vec2 abs);

    virtual void AddControl(UIControl* control);
    virtual void RemoveControl(UIControl* control);

    void SetLayer(Layer<UIControl*>* layer);

    virtual void Start();

    void InheritRoot();
    UIRoot* GetRoot();
    
    // Get theme used by this UI context
    UITheme* GetTheme();

    bool IsFocused();
    
    void UpdateSelfLayout();
    void UpdateChildLayout();
    
    // Default layout engine, uses parent bounds if possible
    virtual void UpdateLayout();

    // Default layout engine, custom parent bounds are supplied
    // virtual void UpdateLayout(vec2 parentPos, vec2 parentSize);

    virtual void ProcessEvents();

    virtual void Render(RenderContext& context);

    /*
    virtual void SetRoot(UIRoot* root);
    virtual void ClearRoot()
    */
};