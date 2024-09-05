#include <gui/line_prop_window.h>

using namespace gui;

gui::LinePropWindow::LinePropWindow()
    : UiWindow("Line Properties"), m_strokeWidth(1.0f), m_strokeColor(BLACK), m_strokeColorArray{0.0f, 0.0f, 0.0f, 1.0f}
{}

LinePropWindow::~LinePropWindow()
{}

void gui::LinePropWindow::setStrokeWidth(float width)
{
    m_strokeWidth = width;
}

void gui::LinePropWindow::setStrokeColor(Color color)
{
    m_strokeColor = color;
}

float gui::LinePropWindow::strokeWidth() const
{
    return m_strokeWidth;
}

Color gui::LinePropWindow::strokeColor() const
{
    Color c{BLACK};
    c.r = static_cast<unsigned char>(std::round(m_strokeColorArray[0] * 255.0f));
    c.g = static_cast<unsigned char>(std::round(m_strokeColorArray[1] * 255.0f));
    c.b = static_cast<unsigned char>(std::round(m_strokeColorArray[2] * 255.0f));
    c.a = static_cast<unsigned char>(std::round(m_strokeColorArray[3] * 255.0f));
    return c;
}

std::shared_ptr<LinePropWindow> gui::LinePropWindow::create()
{
    return std::make_shared<LinePropWindow>();
}

void gui::LinePropWindow::doDraw()
{
    ImGui::Text("Stroke Properties");

    ImGui::SliderFloat("Width", &m_strokeWidth, 1.0f, 100.0f);
    ImGui::ColorEdit4("Color", m_strokeColorArray, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreviewHalf);
}
