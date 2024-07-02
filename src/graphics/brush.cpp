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
    BeginBlendMode(BLEND_ADDITIVE);
    DrawCircle(x, y, m_radius, Color{0, 0, 0, m_hardness});
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

float Brush::radius() const
{
    return m_radius;
}

unsigned char Brush::hardness() const
{
    return m_hardness;
}
