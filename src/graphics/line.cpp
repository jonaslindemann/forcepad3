#include <graphics/line.h>

#include <raylib.h>
#include <raymath.h>
#include <cmath>

using namespace graphics;

std::shared_ptr<Line> graphics::Line::create()
{
    return std::make_shared<Line>();
}

void graphics::Line::setP0(Vector2 p0)
{
    m_p0 = p0;
}

Vector2 graphics::Line::p0() const
{
    return m_p0;
}

void graphics::Line::setP1(Vector2 p1)
{
    m_p1 = p1;
}

Vector2 graphics::Line::p1() const
{
    return m_p1;
}

void graphics::Line::doDraw()
{
    DrawLineEx(m_p0, m_p1, strokeWidth(), strokeColor());
}

void graphics::Line::doDrawOutline()
{
    DrawLineEx(m_p0, m_p1, strokeWidth(), strokeColor());
}

void graphics::Line::doDrawHover()
{
    DrawLineEx(m_p0, m_p1, strokeWidth(), hoverOutlineColor());
}

bool graphics::Line::doIsInside(float x, float y)
{
    const float margin = 5.0f; // Additional margin for "close to the line" check
    const float halfWidth = strokeWidth() / 5.0f + margin;

    // Vector from p0 to p1
    Vector2 lineVec = Vector2Subtract(m_p1, m_p0);

    // Vector from p0 to the point
    Vector2 pointVec = {x - m_p0.x, y - m_p0.y};

    // Length of the line
    float lineLength = Vector2Length(lineVec);

    // Early exit if the line has zero length
    if (lineLength < 0.0001f)
    {
        return (fabsf(x - m_p0.x) <= halfWidth && fabsf(y - m_p0.y) <= halfWidth);
    }

    // Normalize the line vector
    Vector2 lineVecNormalized = Vector2Normalize(lineVec);

    // Project pointVec onto the line
    float projection = Vector2DotProduct(pointVec, lineVecNormalized);

    // Check if the projection is within the line segment
    if (projection < 0 || projection > lineLength)
    {
        return false;
    }

    // Calculate the distance from the point to the line
    Vector2 projectedPoint = Vector2Scale(lineVecNormalized, projection);
    float distance = Vector2Length(Vector2Subtract(pointVec, projectedPoint));

    // Check if the distance is within the line width (including margin)
    return distance <= halfWidth;
}

void graphics::Line::doMove(float x, float y)
{
    Vector2 delta = Vector2Subtract({x, y}, m_p0);
    m_p0 = Vector2Add(m_p0, delta);
    m_p1 = Vector2Add(m_p1, delta);
}

void graphics::Line::doTranslate(float dx, float dy)
{
    m_p0 = Vector2Add(m_p0, {dx, dy});
    m_p1 = Vector2Add(m_p1, {dx, dy});
}

graphics::BoundingBox graphics::Line::doUpdateBoundingBox()
{
    return BoundingBox(std::min(m_p0.x, m_p1.x), std::min(m_p0.y, m_p1.y), std::max(m_p0.x, m_p1.x),
                       std::max(m_p0.y, m_p1.y));
}

void graphics::Line::doUpdateFromBounds(const BoundingBox &bounds)
{
    //                 m_p1
    //  + ------------- +
    //  |             / |
    //  |           /   |
    //  |         /     |
    //  |       /       |
    //  |     /         |
    //  |   /           |
    //  | /             |
    //  + ------------- +
    // m_p0
    //

    std::printf("bounds: left: %f, top: %f, right: %f, bottom: %f\n", bounds.left(), bounds.top(), bounds.right(),
                bounds.bottom());

    if (m_p0.x < m_p1.x)
    {
        m_p0.x = bounds.left();
        m_p1.x = bounds.right();
    }
    else
    {
        m_p0.x = bounds.right();
        m_p1.x = bounds.left();
    }

    if (m_p0.y < m_p1.y)
    {
        m_p0.y = bounds.top();
        m_p1.y = bounds.bottom();
    }
    else
    {
        m_p0.y = bounds.bottom();
        m_p1.y = bounds.top();
    }
}

void graphics::Line::doSetPos(float x, float y)
{
    Vector2 delta = Vector2Subtract({x, y}, m_p0);
    m_p0 = Vector2Add(m_p0, delta);
    m_p1 = Vector2Add(m_p1, delta);
}

void graphics::Line::doGetPos(float &x, float &y)
{
    x = m_p0.x;
    y = m_p0.y;
}
