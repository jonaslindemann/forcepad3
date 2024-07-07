#pragma once

#include <memory>
#include <string>
#include <vector>
#include <functional>

#include <gui/ui_window.h>

#include <raylib.h>

namespace gui {

typedef std::function<void(Color color)> ColorChangedFunc;

class ColorPicker : public UiWindow {
private:
    Color m_color{0, 0, 0, 255};
    float m_colorArray[4] = {0, 0, 0, 1};
    ColorChangedFunc m_onColorChanged;

public:
    ColorPicker();
    virtual ~ColorPicker();

    static std::shared_ptr<ColorPicker> create();

    void setColor(Color color);
    Color getColor();

    void assignOnColorChanged(const gui::ColorChangedFunc &onColorChanged);

protected:
    virtual void doDraw();
};

typedef std::shared_ptr<ColorPicker> ColorPickerPtr;

} // namespace gui
