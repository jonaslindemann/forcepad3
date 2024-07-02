#pragma once

#include <memory>

#include "raylib.h"
#include "gui/raylib_window.h"
#include "graphics/raylib_image.h"
#include "graphics/raylib_texture.h"
#include "graphics/raylib_render_texture.h"
#include <graphics/brush.h>

namespace forcepad {

enum class DrawingMode {
    Brush,
    Eraser,
    Rectangle,
    Ellipse,
    Line,
    Select,
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
    graphics::RaylibRenderTexturePtr m_renderTexture;

    AppMode m_appMode;
    DrawingMode m_drawingMode;
    PhysicsMode m_physicsMode;

    graphics::BrushPtr m_brush;

    bool m_showMessageBox;

public:
    ForcePadWindow(int width, int height, std::string title);

    static std::shared_ptr<ForcePadWindow> create(int width, int height, std::string title);

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
};

typedef std::shared_ptr<ForcePadWindow> ForcePadWindowPtr;

} // namespace forcepad
