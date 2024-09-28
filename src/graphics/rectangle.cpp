#include <graphics/rectangle.h>

#include <cmath>

using namespace graphics;

std::shared_ptr<graphics::Rectangle> graphics::Rectangle::create()
{
    return std::make_shared<Rectangle>();
}

void graphics::Rectangle::setP0(Vector2 p0)
{
    m_p0 = p0;
}

Vector2 graphics::Rectangle::p0() const
{
    return m_p0;
}

void graphics::Rectangle::setP1(Vector2 p1)
{
    m_p1 = p1;
}

Vector2 graphics::Rectangle::p1() const
{
    return m_p1;
}

void graphics::Rectangle::setSize(Vector2 size)
{
    m_p1 = {m_p0.x + size.x, m_p0.y + size.y};
}

Vector2 graphics::Rectangle::size() const
{
    return {m_p1.x - m_p0.x, m_p1.y - m_p0.y};
}

Vector2 graphics::Rectangle::upperLeft()
{
    Vector2 p0{0.0f, 0.0f};

    if (m_p0.x < m_p1.x)
        p0.x = m_p0.x;
    else
        p0.x = m_p1.x;

    if (m_p0.y < m_p1.y)
        p0.y = m_p0.y;
    else
        p0.y = m_p1.y;

    return p0;
}

Vector2 graphics::Rectangle::lowerRight()
{
    Vector2 p1{0.0f, 0.0f};

    if (m_p0.x < m_p1.x)
        p1.x = m_p1.x;
    else
        p1.x = m_p0.x;

    if (m_p0.y < m_p1.y)
        p1.y = m_p1.y;
    else
        p1.y = m_p0.y;

    return p1;
}

void graphics::Rectangle::doDraw()
{
    Vector2 p0 = upperLeft();
    Vector2 p1 = lowerRight();

    Vector2 vSize = {p1.x - p0.x, p1.y - p0.y};

    DrawRectangleV(p0, vSize, fillColor());
    DrawRectangleLinesEx({p0.x, p0.y, std::fabs(p1.x - p0.x), std::fabs(p1.y - p0.y)}, strokeWidth(), strokeColor());
}

void graphics::Rectangle::doDrawOutline()
{
    Vector2 p0 = upperLeft();
    Vector2 p1 = lowerRight();

    DrawRectangleLinesEx({p0.x, p0.y, std::fabs(p1.x - p0.x), std::fabs(p1.y - p0.y)}, outlineWidth(), outlineColor());
}

void graphics::Rectangle::doDrawHover()
{
    Vector2 p0 = upperLeft();
    Vector2 p1 = lowerRight();

    Vector2 vSize = {p1.x - p0.x, p1.y - p0.y};

    DrawRectangleV(p0, vSize, hoverColor());
    DrawRectangleLinesEx({p0.x, p0.y, std::fabs(p1.x - p0.x), std::fabs(p1.y - p0.y)}, strokeWidth(),
                         hoverOutlineColor());
}

bool graphics::Rectangle::doIsInside(float x, float y)
{
    Vector2 p0 = upperLeft();
    Vector2 p1 = lowerRight();

    Vector2 vSize = {p1.x - p0.x, p1.y - p0.y};

    return (x >= p0.x && x <= p1.x && y >= p0.y && y <= p1.y);
}

void graphics::Rectangle::doMove(float x, float y)
{
    Vector2 p0 = upperLeft();
    Vector2 p1 = lowerRight();

    Vector2 vSize = {p1.x - p0.x, p1.y - p0.y};

    m_p0 = {x, y};
    m_p1 = {x + vSize.x, y + vSize.y};
}

graphics::BoundingBox graphics::Rectangle::doUpdateBoundingBox()
{
    Vector2 p0 = upperLeft();
    Vector2 p1 = lowerRight();
    return BoundingBox(p0.x, p0.y, p1.x, p1.y);
}

void graphics::Rectangle::doUpdateFromBounds(const BoundingBox &bounds)
{
    m_p0 = {bounds.left(), bounds.top()};
    m_p1 = {bounds.right(), bounds.bottom()};
}
