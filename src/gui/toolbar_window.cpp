#include <gui/toolbar_window.h>

#include <graphics/raylib_image.h>

#include <rlimgui/rlImGui.h>

using namespace gui;
using namespace graphics;

ToolbarWindow::ToolbarWindow(const std::string name)
    : UiWindow(name), m_selectedButton{-1}, m_selectedColor{0.3, 0.3, 0.3, 1.0}, m_color{0.0, 0.0, 0.0, 1.0}
{
    setWindowFlags(ImGuiWindowFlags_NoCollapse);
    setCanClose(false);
    setAutoPlacement(false);

    m_color = ImGui::GetStyle().Colors[ImGuiCol_Button];
    // m_selectedColor = {1.0, 1.0, 1.0, 1.0};
}

ToolbarWindow::~ToolbarWindow()
{}

void gui::ToolbarWindow::addButton(const std::string name, ToolbarButtonType type, std::string filename, int group)
{
    auto texture = RaylibTexture::create();
    auto image = RaylibImage::create();
    image->loadFromFile(filename);
    texture->loadFromImage(image);

    m_buttons.emplace_back(name, type, texture, group, texture->texture().id);
}
void gui::ToolbarWindow::addSpacer()
{
    m_buttons.emplace_back("", ToolbarButtonType::Spacer, nullptr, -1, -1);
}
void gui::ToolbarWindow::addToolbarGroup(std::shared_ptr<ToolbarWindow> toolbar)
{
    m_toolbarGroup.push_back(toolbar);
}

void gui::ToolbarWindow::selectButton(int idx, int group)
{
    if (idx < 0 || idx >= m_buttons.size())
    {
        return;
    }

    if (group >= 0)
    {
        for (auto &button : m_buttons)
        {
            if (button.group() == group)
            {
                button.unselect();
            }
        }

        for (auto &toolbar : m_toolbarGroup)
        {
            for (auto &button : toolbar->m_buttons)
            {
                if (button.group() == group)
                {
                    button.unselect();
                }
            }
        }
    }

    m_buttons[idx].select();
    m_selectedButton = idx;
}
gui::ToolbarButton &gui::ToolbarWindow::button(int idx)
{
    return m_buttons[idx];
}

size_t gui::ToolbarWindow::buttonCount()
{
    return m_buttons.size();
}

void ToolbarWindow::update()
{}

void gui::ToolbarWindow::assignOnButtonClicked(const ButtonClickedFunc &onButtonClicked)
{
    m_onButtonClicked = onButtonClicked;
}

void gui::ToolbarWindow::assignOnButtonHover(const ButtonHoverFunc &onButtonHover)
{
    m_onButtonHover = onButtonHover;
}

std::shared_ptr<ToolbarWindow> ToolbarWindow::create(const std::string name)
{
    return std::make_shared<ToolbarWindow>(name);
}

void ToolbarWindow::doDraw()
{
    // ImGui::Dummy(ImVec2(150.0, 0.0));

    this->update();

    ImVec2 button_sz(40, 40);

    ImGuiStyle &style = ImGui::GetStyle();
    int buttons_count = 20;
    float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

    int id = 0;

    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4{1, 0, 0, 1});

    for (auto &button : m_buttons)
    {
        ImGui::PushID(id++);

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4, 4});

        // if (button.texture() != nullptr)
        //     button.texture()->bind();

        if (button.type() == ToolbarButtonType::Button)
        {
            // ImageButton(const char *str_id, ImTextureID user_texture_id, const ImVec2 &image_size,
            //             const ImVec2 &uv0 = ImVec2(0, 0), const ImVec2 &uv1 = ImVec2(1, 1),
            //             const ImVec4 &bg_col = ImVec4(0, 0, 0, 0), const ImVec4 &tint_col = ImVec4(1, 1, 1, 1));

            // if (ImGui::ImageButton("Blah", (ImTextureID)(button.texture()->id()), button_sz, ImVec2(0, 0), ImVec2(1,
            // 1),
            //                        m_color, m_selectedColor))

            // if (ImGui::ImageButton("Blah", (ImTextureID)button.texture()->id(), button_sz, ImVec2(0, 0), ImVec2(1,
            // 1),
            //                       m_color, m_selectedColor))

            if (rlImGuiImageButtonSize("Blah", button.texture()->texturePtr(), ImVec2(50, 50)))
            {
                if (m_onButtonClicked)
                {
                    m_onButtonClicked(button);
                }
            }
            if (ImGui::IsItemHovered())
            {
                if (m_onButtonHover)
                    m_onButtonHover(button);
            }
        }
        else if (button.type() == ToolbarButtonType::ToggleButton)
        {
            if (button.selected())
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0, 0, 1, 1});
            }
            else
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0, 0, 0.5, 1.0});
            }
            if (rlImGuiImageButtonSize("Blah", button.texture()->texturePtr(), ImVec2(50, 50)))
            {
                button.toggleSelected();
                if (m_onButtonClicked)
                {
                    m_onButtonClicked(button);
                }
            }
            if (ImGui::IsItemHovered())
            {
                if (m_onButtonHover)
                    m_onButtonHover(button);
            }
            ImGui::PopStyleColor(1);
        }
        else if (button.type() == ToolbarButtonType::RadioButton)
        {

            if (button.selected())
            {
                ImGui::PushStyleColor(ImGuiCol_Button, m_selectedColor);
            }
            else
            {
                ImGui::PushStyleColor(ImGuiCol_Button, m_color);
            }
            if (rlImGuiImageButtonSize("Blah", button.texture()->texturePtr(), ImVec2(50, 50)))
            {
                this->selectButton(id - 1, button.group());
                if (m_onButtonClicked)
                {
                    m_onButtonClicked(button);
                }
            }
            if (ImGui::IsItemHovered())
            {
                if (m_onButtonHover)
                    m_onButtonHover(button);
            }
            ImGui::PopStyleColor(1);
        }
        else if (button.type() == ToolbarButtonType::Spacer)
        {
            ImGui::Dummy(ImVec2(10, 10));
        }

        // if (button.texture() != nullptr)
        //     button.texture()->unbind();

        ImGui::PopStyleVar(1);
        float last_button_x2 = ImGui::GetItemRectMax().x;
        float next_button_x2 =
            last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
        if (id < buttons_count && next_button_x2 < window_visible_x2)
            ImGui::SameLine();
        ImGui::PopID();
    }
    ImGui::PopStyleColor(1);
}

ToolbarButton::ToolbarButton(const std::string name, ToolbarButtonType type, graphics::RaylibTexturePtr texture,
                             int group, int id)
    : m_name{name}, m_selected{false}, m_enabled{true}, m_group{group}, m_id{id}, m_type{type}, m_texture{texture}
{}

void gui::ToolbarButton::setSelected(bool flag)
{
    m_selected = flag;
}

bool gui::ToolbarButton::selected()
{
    return m_selected;
}

void gui::ToolbarButton::toggleSelected()
{
    m_selected = !m_selected;
}

void gui::ToolbarButton::select()
{
    m_selected = true;
}

void gui::ToolbarButton::unselect()
{
    m_selected = false;
}

void gui::ToolbarButton::setEnabled(bool flag)
{
    m_enabled = flag;
}

bool gui::ToolbarButton::enabled()
{
    return m_enabled;
}

void gui::ToolbarButton::enable()
{
    m_enabled = true;
}

void gui::ToolbarButton::disable()
{
    m_enabled = false;
}

int gui::ToolbarButton::group()
{
    return m_group;
}

int gui::ToolbarButton::id()
{
    return m_id;
}

graphics::RaylibTexturePtr gui::ToolbarButton::texture()
{
    return m_texture;
}

ToolbarButtonType gui::ToolbarButton::type()
{
    return m_type;
}

std::string gui::ToolbarButton::name()
{
    return m_name;
}

void gui::ToolbarButton::setName(const std::string name)
{
    m_name = name;
}
