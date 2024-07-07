#include <gui/color_picker.h>

#include <raylib.h>
#include <imgui.h>

namespace gui {

ColorPicker::ColorPicker() : UiWindow("Color picker"), m_color(RAYWHITE), m_colorArray{1, 1, 1, 1}
{}

ColorPicker::~ColorPicker()
{}

std::shared_ptr<ColorPicker> ColorPicker::create()
{
    return std::make_shared<ColorPicker>();
}

void ColorPicker::setColor(Color color)
{
    m_color = color;
    m_colorArray[0] = m_color.r / 255.0f;
    m_colorArray[1] = m_color.g / 255.0f;
    m_colorArray[2] = m_color.b / 255.0f;
}

Color ColorPicker::getColor()
{
    return m_color;
}

void ColorPicker::assignOnColorChanged(const gui::ColorChangedFunc &onColorChanged)
{
    m_onColorChanged = onColorChanged;
}

void ColorPicker::doDraw()
{
    ImGui::ColorPicker4("Color", m_colorArray,
                        ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip |
                            ImGuiColorEditFlags_DisplayRGB);

    m_color.r = m_colorArray[0] * 255;
    m_color.g = m_colorArray[1] * 255;
    m_color.b = m_colorArray[2] * 255;

    if (m_onColorChanged)
        m_onColorChanged(m_color);
}

} // namespace gui
