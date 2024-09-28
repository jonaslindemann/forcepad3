#include <graphics/ellipse.h>

using namespace graphics;

#include <cmath>

std::shared_ptr<Ellipse> graphics::Ellipse::create()
{
    return std::make_shared<Ellipse>();
}

void graphics::Ellipse::setP0(Vector2 p0)
{
    m_p0 = p0;
}

Vector2 graphics::Ellipse::p0() const
{
    return m_p0;
}

void graphics::Ellipse::setRadiusX(float radiusX)
{
    m_radiusX = std::fabs(radiusX);
}

float graphics::Ellipse::radiusX() const
{
    return m_radiusX;
}

void graphics::Ellipse::setRadiusY(float radiusY)
{
    m_radiusY = std::fabs(radiusY);
}

float graphics::Ellipse::radiusY() const
{
    return m_radiusY;
}

void graphics::Ellipse::doDraw()
{
    DrawEllipse(m_p0.x, m_p0.y, m_radiusX, m_radiusY, fillColor());
    DrawEllipseLines(m_p0.x, m_p0.y, m_radiusX, m_radiusY, strokeColor());
}

void graphics::Ellipse::doDrawOutline()
{
    DrawEllipseLines(m_p0.x, m_p0.y, m_radiusX, m_radiusY, outlineColor());
}

void graphics::Ellipse::doDrawHover()
{
    DrawEllipse(m_p0.x, m_p0.y, m_radiusX, m_radiusY, hoverColor());
    DrawEllipseLines(m_p0.x, m_p0.y, m_radiusX, m_radiusY, hoverOutlineColor());
}

bool graphics::Ellipse::doIsInside(float x, float y)
{
    auto dx = x - m_p0.x;
    auto dy = y - m_p0.y;
    return (dx * dx) / (m_radiusX * m_radiusX) + (dy * dy) / (m_radiusY * m_radiusY) <= 1.0f;
}

void graphics::Ellipse::doMove(float x, float y)
{
    m_p0.x = x;
    m_p0.y = y;
}

graphics::BoundingBox graphics::Ellipse::doUpdateBoundingBox()
{
    return BoundingBox(m_p0.x - m_radiusX, m_p0.y - m_radiusY, m_p0.x + m_radiusX, m_p0.y + m_radiusY);
}

void graphics::Ellipse::doUpdateFromBounds(const BoundingBox &bounds)
{
    m_p0.x = (bounds.left() + bounds.right()) / 2.0f;
    m_p0.y = (bounds.top() + bounds.bottom()) / 2.0f;
    m_radiusX = (bounds.right() - bounds.left()) / 2.0f;
    m_radiusY = (bounds.bottom() - bounds.top()) / 2.0f;
}
