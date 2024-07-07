#include <gui/layer_window.h>

#include <format>

#include <imgui.h>

using namespace gui;

LayerWindow::LayerWindow() : UiWindow("Layer Window"), m_drawing(nullptr)
{
    setWindowFlags(ImGuiWindowFlags_None);
    setAutoPlacement(false);
    // this->setSize(200, 400);

    m_layerVisible.fill(true);
    m_layerColor.fill(ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
}

LayerWindow::~LayerWindow()
{}

void gui::LayerWindow::setDrawing(graphics::DrawingPtr drawing)
{
    m_drawing = drawing;
}

graphics::DrawingPtr gui::LayerWindow::drawing()
{
    return m_drawing;
}

std::shared_ptr<LayerWindow> LayerWindow::create()
{
    return std::make_shared<LayerWindow>();
}

void TextCentered(std::string text)
{
    auto windowWidth = ImGui::GetWindowSize().x;
    auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::Text(text.c_str());
}

void gui::LayerWindow::doDraw()
{
    if (m_drawing != nullptr)
    {
        if (ImGui::Button("Add"))
            m_drawing->addLayer();

        ImGui::SameLine();
        ImGui::Button("Remove");
        ImGui::Separator();

        for (int i = 0; i < m_drawing->layerCount(); i++)
        {
            m_layerVisible[i] = m_drawing->layerProp(i).visible();
            Color c = m_drawing->layerProp(i).tint();
            m_layerColor[i] = ImVec4(c.r / 255.0f, c.g / 255.0f, c.b / 255.0f, c.a / 255.0f);
        }

        for (int n = 0; n < m_drawing->layerCount(); n++)
        {
            if (ImGui::RadioButton(std::format("##current{:d}", n).c_str(), m_drawing->currentLayerIndex() == n))
            {
                m_drawing->setCurrentLayer(n);
            }
            ImGui::SameLine();
            if (ImGui::Checkbox(std::format("##visible{:d}", n).c_str(), &m_layerVisible[n]))
            {
                m_drawing->layerProp(n).setVisible(m_layerVisible[n]);
            }

            ImGui::SameLine();

            if (ImGui::ColorEdit4(std::format("Tint##{:d}", n).c_str(), (float *)&m_layerColor[n],
                                  ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel))
            {
                m_drawing->layerProp(n).setTint(Color(m_layerColor[n].x * 255, m_layerColor[n].y * 255,
                                                      m_layerColor[n].z * 255, m_layerColor[n].w * 255));
            }

            ImGui::SameLine(200);
            // TextCentered(m_drawing->layerProp(n).name());
            ImGui::Text(m_drawing->layerProp(n).name().c_str());
        }
        /*
        if (ImGui::BeginListBox("##test", ImVec2(-FLT_MIN, -FLT_MIN)))
        {
            for (int n = 0; n < m_drawing->layerCount(); n++)
            {
                const bool is_selected = (m_drawing->currentLayerIndex() == n);
                if (ImGui::Selectable(m_drawing->layerProp(n).name().c_str(), is_selected))
                    m_drawing->setCurrentLayer(n);

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        */
    }
}

void gui::LayerWindow::doPreDraw()
{}
