#pragma once

#include <memory>
#include <string>
#include <vector>
#include <functional>

#include <gui/ui_window.h>

#include <raylib.h>

namespace gui {

class LinePropWindow : public UiWindow {
private:
    float m_strokeWidth{1.0f};
    Color m_strokeColor{BLACK};
    float m_strokeColorArray[4]{0.0f, 0.0f, 0.0f, 1.0f};

public:
    LinePropWindow();
    virtual ~LinePropWindow();

    void setStrokeWidth(float width);
    void setStrokeColor(Color color);

    float strokeWidth() const;
    Color strokeColor() const;

    static std::shared_ptr<LinePropWindow> create();

protected:
    virtual void doDraw();
};

typedef std::shared_ptr<LinePropWindow> LinePropWindowPtr;

} // namespace gui
