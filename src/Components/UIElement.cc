#include "UIElement.hh"

UIElement::UIElement(Material* material) : material(material) { }
UIElement::~UIElement() { }

Material* UIElement::GetMaterial()
{
    return material;
}

void UIElement::Setup() { }