#pragma once

#include "UIListBox.hh"

template<typename T>
UIListBox<T>::UIListBox(vec2 position, vec2 size, GlyphSet* font)
: UIControl(position, size), font(font), items(), selected(-1)
{
    focusable = true;
    cursor = CursorMode::Hand;

    events->MouseClickEvent.Subscribe([&](vec2* pos){
        auto relative = GetRelativePosition(*pos);
        selected = relative.y / (16 + padding.y);
        if (selected >= items.size())
            selected = -1;
    });
}


template<typename T>
void UIListBox<T>::AddItem(std::wstring text, T item)
{
    items.push_back(std::make_pair(text, item));
}

template<typename T>
void UIListBox<T>::RemoveItem(T item)
{
    auto it = std::find(items.begin(), items.end(), item);
    items.erase(it);
    selected = -1;
}

template<typename T>
void UIListBox<T>::RemoveAt(size_t index)
{
    items.erase(items.begin() + index);
    selected = -1;
}

template<typename T>
T* UIListBox<T>::GetItem(size_t index)
{
    return &(*(items.begin() + index));
}

template<typename T>
T* UIListBox<T>::GetSelectedItem()
{
    if (selected < 0 || selected >= items.size())
        return nullptr;
    return &(*(items.begin() + selected));
}

template<typename T>
int UIListBox<T>::GetSelectedIndex()
{
    return selected;
}

template<typename T>
size_t UIListBox<T>::Count()
{
    return items.size();
}

template<typename T>
void UIListBox<T>::Render(RenderContext& context)
{
    context.RenderUIQuad(position, size, 0, GetTheme()->Surface(), material);

    if (selected != -1)
        context.RenderUIQuad(vec2(position.x, position.y + selected * (16 + padding.y) - 4), vec2(size.x, 16), 0, GetTheme()->SecondaryAlt(), material);
    
    size_t i = 0;
    // FIXME: renders last-to-first somehow, fix it
    for (auto it = items.begin(); it != items.end(); it++)
    {
        auto height = position.y + i * (16 + padding.y);
        context.RenderUIText(it->first, vec2(position.x + padding.x, height + 8), 0, font, GetTheme()->OnSecondary(), material);
        i++;
    }
}