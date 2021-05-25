#include "UIBarGraph.hh"

UIBarGraph::UIBarGraph(vec2 position, vec2 size, GlyphSet* font)
    : UIControl(position, size), data(), font(font)
{ }

void UIBarGraph::Render(RenderContext& context)
{
    if (data.size() == 0)
        context.RenderUIText("No data to display", position, 0, font, GetTheme()->OnSecondary(), material);
    else
    {
        size_t i = 0;
        auto max = max_element(data.begin(), data.end());
        auto factor = size.y / *max;
        for (auto it = data.begin(); it != data.end(); it++)
        {
            auto height = factor * *it;
            auto left = position.x + 8 + i * (16 + padding.x);
            auto top = position.y + size.y - height;
            context.RenderUIQuad(vec2(left, top), vec2(16, height), 0, GetTheme()->Secondary(), material);
            context.RenderUIText(std::to_string(*it), vec2(left, size.y + 4), 0, font, GetTheme()->OnSecondary(), material);
            i++;
        }
    }
    context.RenderUIRect(position, size, 0, 1, GetTheme()->Primary(), material);
}