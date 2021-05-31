#pragma once

#include "../UIControl.hh"
#include "UIListBox.hh"

template<typename T>
class UIComboBox : public UIControl
{
    UIListBox<T>* list;

public:
    GlyphSet* font;

    UIComboBox(vec2 position, vec2 size, GlyphSet* font);

    void Start();
    
    void AddItem(std::wstring text, T data);
    
    void RemoveItem(std::wstring text);
    void RemoveAt(size_t index);

    T* GetItem(size_t index);
    T* GetSelectedItem();
    int GetSelectedIndex();

    void UpdateLayout();

    void Render(RenderContext& context);
};

#include "UIComboBox.ipp"