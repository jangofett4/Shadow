#pragma once

#include "../UIControl.hh"

template<typename T>
class UIListBox : public UIControl
{
    int selected;

public:
    std::vector<std::pair<std::wstring, T>> items;
    GlyphSet* font;

    UIListBox(vec2 position, vec2 size, GlyphSet* font);

    void AddItem(std::wstring text, T item);
    
    void RemoveItem(T item);
    void RemoveAt(size_t index);

    T* GetItem(size_t index);
    
    T* GetSelectedItem();
    int GetSelectedIndex();

    size_t Count();

    void Render(RenderContext& context);
};

#include "UIListBox.ipp"