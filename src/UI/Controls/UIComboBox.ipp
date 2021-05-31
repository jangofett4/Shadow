#pragma once

#include "UIComboBox.hh"

template<typename T>
UIComboBox<T>::UIComboBox(vec2 position, vec2 size, GlyphSet* font)
    : UIControl(position, size), font(font)
{
    cursor = CursorMode::Hand;
    focusable = true;
    list = new UIListBox<T>(vec2(), vec2(50), font);
    list->visible = false;
}

template<typename T>
void UIComboBox<T>::Start()
{
    UIControl::Start();

    list->SetLayer(GetRoot()->Layers.Popup);
    AddControl(list);
}

template<typename T>
void UIComboBox<T>::AddItem(std::wstring text, T data)
{
    list->AddItem(text, data);
}

template<typename T>
void UIComboBox<T>::RemoveItem(std::wstring text)
{
    auto found = list->items.find(text);
    if (found == list->items.end())
        return;
    list->items.erase(found);
}

template<typename T>
void UIComboBox<T>::RemoveAt(size_t index)
{
    if (index < 0 || index >= list->items.size())
        return;
    list->items.erase(list->items.begin() + index);
}

template<typename T>
T* UIComboBox<T>::GetItem(size_t index)
{
    return list->GetItem(index);
}

template<typename T>
T* UIComboBox<T>::GetSelectedItem()
{
    auto index = GetSelectedIndex();
    if (index < 0)
        return nullptr;
    return GetItem(index);
}

template<typename T>
int UIComboBox<T>::GetSelectedIndex()
{
    return list->GetSelectedIndex();
}

template<typename T>
void UIComboBox<T>::UpdateLayout()
{
    UpdateSelfLayout();

    list->position = vec2(position.x, position.y + size.y + padding.y * 2);
    list->size.x = size.x;
}

template<typename T>
void UIComboBox<T>::Render(RenderContext& context)
{
    auto theme = GetTheme();
    bool focus = IsFocused();
    vec4 color = theme->Secondary();

    // TODO: this is SO BAD. Implement OnFocusChange then move these there
    if (focus)
    {
        list->visible = true;
        /*
        size_t i = 0;
        for (auto it = list->items.begin(); it != list->items.end(); it++)
        {
            auto top = position.y + size.y + padding.y + i * (18 + padding.y);
            context.RenderUIRect(vec2(position.x, top), vec2(size.x, 18), 0, 1, theme->SecondaryAlt(), material);
            context.RenderUIText(it->first, vec2(position.x + padding.x, top + 12), 0, font, theme->OnSurface(), material);
            //context.RenderUIQuad(vec2(position.x, position.y + size.y + padding.y + i * (14 + padding.y)), vec2(size.x, 14), 0, theme->PrimaryAlt(), material);
            i++;
        }
        */
    }
    else
        list->visible = false;

    context.RenderUIQuad(vec2(position.x, position.y + size.y - 2), vec2(size.x, 2), 0, color, material);
    auto selected = GetSelectedIndex();
    if (selected < 0)
        context.RenderUIText("Select Option...", vec2(position.x + padding.x, position.y + (size.y / 1.5)), 0, font, theme->OnSurface(), material);
    else
        context.RenderUIText((list->items.begin() + selected)->first, vec2(position.x + padding.x, position.y + (size.y / 1.5)), 0, font, theme->OnSurface(), material);
}