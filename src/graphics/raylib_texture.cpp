#include "graphics/raylib_texture.h"

using namespace graphics;

RaylibTexture::RaylibTexture() : m_texture(), m_loaded(false), m_width(0), m_height(0)
{}

RaylibTexture::~RaylibTexture()
{}

std::shared_ptr<RaylibTexture> graphics::RaylibTexture::create()
{
    return std::make_shared<RaylibTexture>();
}

void RaylibTexture::loadFromImage(RaylibImagePtr image)
{
    m_texture = LoadTextureFromImage(image->image());
    m_width = m_texture.width;
    m_height = m_texture.height;
    m_loaded = true;
}

void graphics::RaylibTexture::updateFromImage(RaylibImagePtr image)
{
    UpdateTexture(m_texture, image->image().data);
}

void RaylibTexture::unload()
{
    UnloadTexture(m_texture);
    m_loaded = false;
}

bool RaylibTexture::isLoaded() const
{
    return m_loaded;
}

Texture2D RaylibTexture::texture() const
{
    return m_texture;
}

Texture2D &graphics::RaylibTexture::texture()
{
    return m_texture;
}

int graphics::RaylibTexture::width() const
{
    return m_width;
}

int graphics::RaylibTexture::height() const
{
    return m_width;
}

float graphics::RaylibTexture::widthF() const
{
    return float(m_width);
}

float graphics::RaylibTexture::heightF() const
{
    return float(m_height);
}
