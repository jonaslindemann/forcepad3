#pragma once

#include <graphics/raylib_texture.h>
#include <gui/ui_window.h>

#include <functional>
#include <vector>

namespace gui {

enum class ToolbarButtonType {
    Button,
    ToggleButton,
    RadioButton,
    Spacer
};

class ToolbarButton {
private:
    std::string m_name;
    ToolbarButtonType m_type;
    bool m_selected;
    bool m_enabled;
    int m_group;
    int m_id;
    graphics::RaylibTexturePtr m_texture;

public:
    ToolbarButton(const std::string name = "Button", ToolbarButtonType type = ToolbarButtonType::Button,
                  graphics::RaylibTexturePtr texture = nullptr, int group = -1, int id = -1);
    virtual ~ToolbarButton() = default;

    void setSelected(bool flag);
    bool selected();
    void toggleSelected();
    void select();
    void unselect();

    void setEnabled(bool flag);
    bool enabled();
    void enable();
    void disable();

    int group();
    int id();

    graphics::RaylibTexturePtr texture();

    ToolbarButtonType type();
    std::string name();
    void setName(const std::string name);
};

typedef std::function<void(ToolbarButton &button)> ButtonClickedFunc;
typedef std::function<void(ToolbarButton &button)> ButtonHoverFunc;

class ToolbarWindow : public UiWindow {
private:
    int m_selectedButton;

    std::vector<ToolbarButton> m_buttons;
    ImVec4 m_selectedColor;
    ImVec4 m_color;

    ButtonClickedFunc m_onButtonClicked;
    ButtonHoverFunc m_onButtonHover;

    std::vector<std::shared_ptr<ToolbarWindow>> m_toolbarGroup;

public:
    ToolbarWindow(const std::string name);
    virtual ~ToolbarWindow();

    void addButton(const std::string name, ToolbarButtonType type = ToolbarButtonType::Button,
                   std::string filename = "", int group = -1);

    void addSpacer();

    void addToolbarGroup(std::shared_ptr<ToolbarWindow> toolbar);

    void selectButton(int idx, int group);

    ToolbarButton &button(int idx);
    size_t buttonCount();

    void update();

    void assignOnButtonClicked(const gui::ButtonClickedFunc &onButtonClicked);
    void assignOnButtonHover(const gui::ButtonHoverFunc &onButtonHover);

    static std::shared_ptr<ToolbarWindow> create(const std::string name);

protected:
    virtual void doDraw();
};

typedef std::shared_ptr<ToolbarWindow> ToolbarWindowPtr;

} // namespace gui
