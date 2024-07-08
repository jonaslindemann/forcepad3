#include "graphics/brush.h"

#include "raylib.h"

using namespace graphics;

Brush::Brush(float radius, float hardness) : m_radius(radius), m_hardness(hardness)
{}

Brush::~Brush()
{}

std::shared_ptr<Brush> graphics::Brush::create(float radius, float hardness)
{
    return std::make_shared<Brush>(radius, hardness);
}

void graphics::Brush::apply(float x, float y)
{
    if (m_blending)
        BeginBlendMode(m_blendMode);

    Color color = m_color;
    // color.a = m_hardness;
    DrawCircle(x, y, m_radius, m_color);

    if (m_blending)
        EndBlendMode();
}

void Brush::setRadius(float radius)
{
    m_radius = radius;
}

void Brush::setHardness(unsigned char hardness)
{
    m_hardness = hardness;
}

void graphics::Brush::setColor(Color color)
{
    m_color = color;
}

void graphics::Brush::setBlendMode(BlendMode blendMode)
{
    m_blendMode = blendMode;
}

void graphics::Brush::setBlending(bool blending)
{
    m_blending = blending;
}

float Brush::radius() const
{
    return m_radius;
}

unsigned char Brush::hardness() const
{
    return m_hardness;
}

Color graphics::Brush::color() const
{
    return m_color;
}

BlendMode graphics::Brush::blendMode() const
{
    return m_blendMode;
}

bool graphics::Brush::blending() const
{
    return m_blending;
}
