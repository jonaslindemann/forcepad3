#pragma once

#include <memory>

#include "raylib.h"

namespace graphics {

class Shape {
private:
    Color m_fillColor{YELLOW};
    Color m_strokeColor{BLUE};
    Color m_outlineColor{RED};
    Color m_hoverColor{GREEN};
    Color m_hoverOutlineColor{BLUE};

    bool m_visible{true};
    bool m_outline{false};
    bool m_hover{false};
    float m_strokeWidth{1.0f};
    float m_outlineWidth{1.0f};

public:
    Shape() = default;
    virtual ~Shape() = default;

    void setFillColor(Color color);
    Color fillColor() const;

    void setStrokeColor(Color color);
    Color strokeColor() const;

    void setOutlineColor(Color color);
    Color outlineColor() const;

    void setStrokeWidth(float width);
    float strokeWidth() const;

    void setOutlineWidth(float width);
    float outlineWidth() const;

    void setVisible(bool visible);
    bool visible() const;

    void setOutline(bool outline);
    bool outline() const;

    void setHover(bool hover);
    bool hover() const;

    void setHoverColor(Color color);
    Color hoverColor() const;

    void setHoverOutlineColor(Color color);
    Color hoverOutlineColor() const;

    void setHoverFromFillAndStroke();

    void draw();

    bool isInside(float x, float y);

protected:
    virtual void doDraw() = 0;
    virtual void doDrawOutline() = 0;
    virtual bool doIsInside(float x, float y) = 0;
    virtual void doDrawHover() = 0;
};

using ShapePtr = std::shared_ptr<Shape>;

} // namespace graphics
