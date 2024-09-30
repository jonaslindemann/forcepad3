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

bool graphics::Shape::isInsideBbox(float x, float y)
{
    return boundingBox().isInside(x, y);
}

void graphics::Shape::move(float x, float y)
{
    doMove(x, y);
}

void graphics::Shape::translate(float dx, float dy)
{
    doTranslate(dx, dy);
}

void graphics::Shape::setPos(float x, float y)
{
    doSetPos(x, y);
}

void graphics::Shape::getPos(float &x, float &y)
{
    doGetPos(x, y);
}

void graphics::Shape::setRotation(float rotation)
{
    m_rotation = rotation;
}

float graphics::Shape::rotation() const
{
    return m_rotation;
}

graphics::BoundingBox &graphics::Shape::boundingBox()
{
    m_boundingBox = doUpdateBoundingBox();
    return m_boundingBox;
}

void graphics::Shape::updateFromBounds(const BoundingBox &bounds)
{
    doUpdateFromBounds(bounds);
}

graphics::BoundingBox::BoundingBox(float left, float top, float right, float bottom)
    : m_left(left), m_top(top), m_right(right), m_bottom(bottom)
{}

void graphics::BoundingBox::setLeft(float left)
{
    m_left = left;
}

float graphics::BoundingBox::left() const
{
    return m_left;
}

void graphics::BoundingBox::setTop(float top)
{
    m_top = top;
}

float graphics::BoundingBox::top() const
{
    return m_top;
}

void graphics::BoundingBox::setRight(float right)
{
    m_right = right;
}

float graphics::BoundingBox::right() const
{
    return m_right;
}

void graphics::BoundingBox::setBottom(float bottom)
{
    m_bottom = bottom;
}

float graphics::BoundingBox::bottom() const
{
    return m_bottom;
}

float graphics::BoundingBox::width() const
{
    return abs(m_right - m_left);
}

float graphics::BoundingBox::height() const
{
    return abs(m_bottom - m_top);
}

bool graphics::BoundingBox::isInside(float x, float y)
{
    return x >= m_left && x <= m_right && y >= m_top && y <= m_bottom;
}
