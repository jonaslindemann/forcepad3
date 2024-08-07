#pragma once

#include <memory>
#include <filesystem>

#include <raylib.h>
#include <gui/raylib_window.h>
#include <graphics/raylib_image.h>
#include <graphics/raylib_texture.h>
#include <graphics/raylib_render_texture.h>
#include <graphics/brush.h>
#include <graphics/drawing.h>

#include <gui/about_window.h>
#include <gui/toolbar_window.h>
#include <gui/color_picker.h>
#include <gui/layer_window.h>

namespace forcepad {

enum class DrawingMode {
    Brush,
    Eraser,
    Rectangle,
    Ellipse,
    Line,
    SelectShape,
    SelectRect,
    Move,
    Copy
};

enum class PhysicsMode {
    Load,
    Constraint,
};

enum class AppMode {
    Material,
    Physics,
    Results
};

class ForcePadWindow : public gui::RaylibWindow {
private:
    std::string m_progPathStr;

    std::filesystem::path m_progPath;
    std::filesystem::path m_imagePath;
    std::filesystem::path m_fontPath;
    // std::filesystem::path m_pluginPath;
    // std::filesystem::path m_mapPath;
    // std::filesystem::path m_pythonPath;
    // std::filesystem::path m_examplePath;

    graphics::RaylibRenderTexturePtr m_renderTexture;
    graphics::RaylibRenderTexturePtr m_overlayTexture;

    graphics::DrawingPtr m_drawing;

    AppMode m_appMode;
    DrawingMode m_drawingMode;
    PhysicsMode m_physicsMode;

    Color m_currentColor;

    graphics::BrushPtr m_brush;
    graphics::BrushPtr m_eraser;

    bool m_showMessageBox;

    gui::AboutWindowPtr m_aboutWindow;
    gui::ToolbarWindowPtr m_toolbarWindow;
    gui::ColorPickerPtr m_colorPicker;
    gui::LayerWindowPtr m_layerWindow;

public:
    ForcePadWindow(int width, int height, std::string title);

    static std::shared_ptr<ForcePadWindow> create(int width, int height, std::string title);

    void setProgPath(std::string path);

    void setAppMode(AppMode mode);
    AppMode appMode() const;

    void setDrawingMode(DrawingMode mode);
    DrawingMode drawingMode() const;

    void setPhysicsMode(PhysicsMode mode);
    PhysicsMode physicsMode() const;

    virtual void onKeyPressed(int key) override;
    virtual void onSetup() override;
    virtual void onUpdate() override;
    virtual void onDraw() override;
    virtual void onDrawGui() override;
    virtual void onResize(int width, int height) override;
    virtual void onMousePressed(gui::MouseButton button, float x, float y) override;
    virtual void onMouseDown(gui::MouseButton button, float x, float y) override;
    virtual void onMouseMove(float x, float y) override;
    virtual void onMouseReleased(gui::MouseButton button, float x, float y) override;

    void onButtonClicked(gui::ToolbarButton &button);
    void onButtonHover(gui::ToolbarButton &button);
    void onColorChanged(Color color);
};

typedef std::shared_ptr<ForcePadWindow> ForcePadWindowPtr;

} // namespace forcepad
