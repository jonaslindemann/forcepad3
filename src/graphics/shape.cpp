#include <graphics/shape.h>

using namespace graphics;

void Shape::setFillColor(Color color)
{
    m_fillColor = color;

    setHoverFromFillAndStroke();
}

Color Shape::fillColor() const
{
    return m_fillColor;
}

void Shape::setStrokeColor(Color color)
{
    m_strokeColor = color;
    setHoverFromFillAndStroke();
}

Color Shape::strokeColor() const
{
    return m_strokeColor;
}

void graphics::Shape::setOutlineColor(Color color)
{
    m_outlineColor = color;
}

Color graphics::Shape::outlineColor() const
{
    return m_outlineColor;
}

void graphics::Shape::setStrokeWidth(float width)
{
    m_strokeWidth = width;
}

float graphics::Shape::strokeWidth() const
{
    return m_strokeWidth;
}

void graphics::Shape::setOutlineWidth(float width)
{
    m_outlineWidth = width;
}

float graphics::Shape::outlineWidth() const
{
    return m_outlineWidth;
}

void Shape::setVisible(bool visible)
{
    m_visible = visible;
}

bool Shape::visible() const
{
    return m_visible;
}

void graphics::Shape::setOutline(bool outline)
{
    m_outline = outline;
}

bool graphics::Shape::outline() const
{
    return m_outline;
}

void graphics::Shape::setHover(bool hover)
{
    m_hover = hover;
}

bool graphics::Shape::hover() const
{
    return m_hover;
}

void graphics::Shape::setHoverColor(Color color)
{
    m_hoverColor = color;
}

Color graphics::Shape::hoverColor() const
{
    return m_hoverColor;
}

void graphics::Shape::setHoverOutlineColor(Color color)
{
    m_hoverOutlineColor = color;
}

Color graphics::Shape::hoverOutlineColor() const
{
    return m_hoverOutlineColor;
}

void graphics::Shape::setHoverFromFillAndStroke()
{
    m_hoverColor = ColorBrightness(m_fillColor, 0.50f);
    m_hoverOutlineColor = ColorBrightness(m_strokeColor, 0.50f);
}

void Shape::draw()
{
    if (m_visible)
    {
        if (m_outline)
            doDrawOutline();
        else
        {
            if (m_hover)
                doDrawHover();
            else
                doDraw();
        }
    }
}

bool graphics::Shape::isInside(float x, float y)
{
    return doIsInside(x, y);
}

void graphics::Shape::move(float x, float y)
{
    doMove(x, y);
}
