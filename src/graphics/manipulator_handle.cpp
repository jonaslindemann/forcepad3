#include <graphics/manipulator_handle.h>
#include <graphics/manipulator.h>

#include <graphics/utils.h>

using namespace graphics;

std::shared_ptr<ManipulatorHandle> graphics::ManipulatorHandle::create()
{
    return std::make_shared<ManipulatorHandle>();
}

void graphics::ManipulatorHandle::setPosition(Vector2 position)
{
    m_position = position;
}

Vector2 graphics::ManipulatorHandle::position() const
{
    return m_position;
}

void graphics::ManipulatorHandle::setRadius(float radius)
{
    m_radius = radius;
}

float graphics::ManipulatorHandle::radius() const
{
    return m_radius;
}

void graphics::ManipulatorHandle::setThickness(float thickness)
{
    m_thickness = thickness;
}

float graphics::ManipulatorHandle::thickness() const
{
    return m_thickness;
}

void graphics::ManipulatorHandle::setManipulator(Manipulator *manipulator)
{
    m_manipulator = manipulator;
}

Manipulator *graphics::ManipulatorHandle::manipulator() const
{
    return m_manipulator;
}

void graphics::ManipulatorHandle::doDraw()
{
    DrawEllipse(m_position.x, m_position.y, m_radius, m_radius, WHITE);
    DrawEllipseLinesEx(m_position.x, m_position.y, m_radius, m_radius, m_thickness, DARKGRAY);
}

void graphics::ManipulatorHandle::doDrawOutline()
{}

void graphics::ManipulatorHandle::doDrawHover()
{}

bool graphics::ManipulatorHandle::doIsInside(float x, float y)
{
    return CheckCollisionPointCircle({x, y}, m_position, m_radius * 2.0);
}

void graphics::ManipulatorHandle::doMove(float x, float y)
{
    m_position.x = x;
    m_position.y = y;

    if (m_manipulator != nullptr)
    {
        m_manipulator->update(this);
    }
}

void graphics::ManipulatorHandle::doTranslate(float dx, float dy)
{
    m_position.x += dx;
    m_position.y += dy;

    if (m_manipulator != nullptr)
    {
        m_manipulator->update(this);
    }
}

graphics::BoundingBox graphics::ManipulatorHandle::doUpdateBoundingBox()
{
    return BoundingBox();
}

void graphics::ManipulatorHandle::doUpdateFromBounds(const BoundingBox &bounds)
{}

void graphics::ManipulatorHandle::doSetPos(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}

void graphics::ManipulatorHandle::doGetPos(float &x, float &y)
{
    x = m_position.x;
    y = m_position.y;
}
