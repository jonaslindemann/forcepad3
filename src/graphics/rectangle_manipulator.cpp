#include <graphics/rectangle_manipulator.h>

#include <graphics/utils.h>

#include <cmath>

using namespace graphics;

std::shared_ptr<RectangleManipulator> graphics::RectangleManipulator::create()
{
    return std::make_shared<RectangleManipulator>();
}

void graphics::RectangleManipulator::setP0(Vector2 p0)
{
    m_p0 = p0;
}

Vector2 graphics::RectangleManipulator::p0() const
{
    return m_p0;
}

void graphics::RectangleManipulator::setP1(Vector2 p1)
{
    m_p1 = p1;
}

Vector2 graphics::RectangleManipulator::p1() const
{
    return m_p1;
}

void graphics::RectangleManipulator::setHandleRadius(float radius)
{
    m_handleRadius = radius;
}

float graphics::RectangleManipulator::handleRadius() const
{
    return m_handleRadius;
}

void graphics::RectangleManipulator::setHandleThickness(float thickness)
{
    m_handleThickness = thickness;
}

float graphics::RectangleManipulator::handleThickness() const
{
    return m_handleThickness;
}

Vector2 graphics::RectangleManipulator::upperLeft()
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

Vector2 graphics::RectangleManipulator::lowerRight()
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

void graphics::RectangleManipulator::doDraw()
{
    Vector2 p0 = upperLeft();
    Vector2 p1 = lowerRight();

    Vector2 vSize = {p1.x - p0.x, p1.y - p0.y};

    DrawRectangleLinesEx({p0.x, p0.y, std::fabs(p1.x - p0.x), std::fabs(p1.y - p0.y)}, 1.0f, DARKGRAY);

    DrawEllipse(m_p0.x, m_p0.y, m_handleRadius, m_handleRadius, WHITE);
    DrawEllipseLinesEx(m_p0.x, m_p0.y, m_handleRadius, m_handleRadius, m_handleThickness, DARKGRAY);

    DrawEllipse(m_p0.x, m_p1.y, m_handleRadius, m_handleRadius, WHITE);
    DrawEllipseLinesEx(m_p0.x, m_p1.y, m_handleRadius, m_handleRadius, m_handleThickness, DARKGRAY);

    DrawEllipse(m_p1.x, m_p1.y, m_handleRadius, m_handleRadius, WHITE);
    DrawEllipseLinesEx(m_p1.x, m_p1.y, m_handleRadius, m_handleRadius, m_handleThickness, DARKGRAY);

    DrawEllipse(m_p1.x, m_p0.y, m_handleRadius, m_handleRadius, WHITE);
    DrawEllipseLinesEx(m_p1.x, m_p0.y, m_handleRadius, m_handleRadius, m_handleThickness, DARKGRAY);

    DrawEllipse(m_p0.x, m_p0.y + vSize.y / 2.0f, m_handleRadius, m_handleRadius, WHITE);
    DrawEllipseLinesEx(m_p0.x, m_p0.y + vSize.y / 2.0f, m_handleRadius, m_handleRadius, m_handleThickness, DARKGRAY);

    DrawEllipse(m_p1.x, m_p0.y + vSize.y / 2.0f, m_handleRadius, m_handleRadius, WHITE);
    DrawEllipseLinesEx(m_p1.x, m_p0.y + vSize.y / 2.0f, m_handleRadius, m_handleRadius, m_handleThickness, DARKGRAY);

    DrawEllipse(m_p0.x + vSize.x / 2.0f, m_p0.y, m_handleRadius, m_handleRadius, WHITE);
    DrawEllipseLinesEx(m_p0.x + vSize.x / 2.0f, m_p0.y, m_handleRadius, m_handleRadius, m_handleThickness, DARKGRAY);

    DrawEllipse(m_p0.x + vSize.x / 2.0f, m_p1.y, m_handleRadius, m_handleRadius, WHITE);
    DrawEllipseLinesEx(m_p0.x + vSize.x / 2.0f, m_p1.y, m_handleRadius, m_handleRadius, m_handleThickness, DARKGRAY);
}

void graphics::RectangleManipulator::doDrawOutline()
{}

void graphics::RectangleManipulator::doDrawHover()
{}

bool graphics::RectangleManipulator::doIsInside(float x, float y)
{
    Vector2 p0 = upperLeft();
    Vector2 p1 = lowerRight();

    Vector2 vSize = {p1.x - p0.x, p1.y - p0.y};

    return (x >= p0.x && x <= p1.x && y >= p0.y && y <= p1.y);
}
