#include "graphics/raylib_render_texture.h"

using namespace graphics;

RaylibRenderTexture::RaylibRenderTexture() : m_texture(), m_loaded(false), m_width(0), m_height(0)
{}

RaylibRenderTexture::~RaylibRenderTexture()
{}

std::shared_ptr<RaylibRenderTexture> graphics::RaylibRenderTexture::create()
{
    return std::make_shared<RaylibRenderTexture>();
}

void graphics::RaylibRenderTexture::load(int width, int height)
{
    m_texture = LoadRenderTexture(width, height);
    m_width = width;
    m_height = height;
    m_loaded = true;
}

void RaylibRenderTexture::unload()
{
    if (!m_loaded)
        return;

    UnloadRenderTexture(m_texture);
    m_loaded = false;
}

bool RaylibRenderTexture::isLoaded() const
{
    return m_loaded;
}

RenderTexture2D RaylibRenderTexture::texture() const
{
    return m_texture;
}

RenderTexture2D &graphics::RaylibRenderTexture::texture()
{
    return m_texture;
}

void graphics::RaylibRenderTexture::beginDraw()
{
    if (!m_loaded)
        return;

    BeginTextureMode(m_texture);
}

void graphics::RaylibRenderTexture::endDraw()
{
    if (!m_loaded)
        return;

    EndTextureMode();
}

void graphics::RaylibRenderTexture::draw(int x, int y, Color tint)
{
    if (!m_loaded)
        return;

    DrawTexture(m_texture.texture, x, y, tint);
}

int graphics::RaylibRenderTexture::width() const
{
    return m_width;
}

int graphics::RaylibRenderTexture::height() const
{
    return m_width;
}

float graphics::RaylibRenderTexture::widthF() const
{
    return float(m_width);
}

float graphics::RaylibRenderTexture::heightF() const
{
    return float(m_height);
}
