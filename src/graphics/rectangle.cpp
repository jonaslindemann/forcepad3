#include <graphics/rectangle.h>

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

void graphics::Rectangle::doDraw()
{
    Vector2 vSize = {m_p1.x - m_p0.x, m_p1.y - m_p0.y};
    DrawRectangleV(m_p0, vSize, fillColor());
    DrawRectangleLinesEx({m_p0.x, m_p0.y, m_p1.x - m_p0.x, m_p1.y - m_p0.y}, strokeWidth(), strokeColor());
}

void graphics::Rectangle::doDrawOutline()
{
    DrawRectangleLinesEx({m_p0.x, m_p0.y, m_p1.x - m_p0.x, m_p1.y - m_p0.y}, outlineWidth(), outlineColor());
}

void graphics::Rectangle::doDrawHover()
{
    Vector2 vSize = {m_p1.x - m_p0.x, m_p1.y - m_p0.y};
    DrawRectangleV(m_p0, vSize, hoverColor());
    DrawRectangleLinesEx({m_p0.x, m_p0.y, m_p1.x - m_p0.x, m_p1.y - m_p0.y}, strokeWidth(), hoverOutlineColor());
}

bool graphics::Rectangle::doIsInside(float x, float y)
{
    return (x >= m_p0.x && x <= m_p1.x && y >= m_p0.y && y <= m_p1.y);
}
