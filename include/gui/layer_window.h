#pragma once

#include <array>

#include <gui/ui_window.h>
#include <graphics/drawing.h>

namespace gui {

class LayerWindow : public UiWindow {
private:
    graphics::DrawingPtr m_drawing;
    std::array<bool, 20> m_layerVisible;
    std::array<ImVec4, 20> m_layerColor;

public:
    LayerWindow();
    virtual ~LayerWindow();

    void setDrawing(graphics::DrawingPtr drawing);
    graphics::DrawingPtr drawing();

    static std::shared_ptr<LayerWindow> create();

protected:
    virtual void doDraw() override;
    virtual void doPreDraw() override;
};

typedef std::shared_ptr<LayerWindow> LayerWindowPtr;

} // namespace gui
