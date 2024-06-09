#include "graphics/raylib_image.h"

using namespace graphics;

RaylibImage::RaylibImage() : m_loaded(false), m_image{}
{}

std::shared_ptr<RaylibImage> RaylibImage::create()
{
    return std::make_shared<RaylibImage>();
}

void RaylibImage::loadFromFile(std::string filename)
{
    if (m_loaded)
        this->unload();

    m_image = LoadImage(filename.c_str());
    m_loaded = true;
}

void graphics::RaylibImage::generateColor(int width, int height, Color color)
{
    if (m_loaded)
        this->unload();

    m_image = GenImageColor(width, height, color);
    m_loaded = true;
}

void graphics::RaylibImage::generateGradientLinear(int width, int height, int direction, Color start, Color end)
{
    if (m_loaded)
        this->unload();

    m_image = GenImageGradientLinear(width, height, direction, start, end);
    m_loaded = true;
}

void graphics::RaylibImage::generateGradientRadial(int width, int height, float density, Color inner, Color outer)
{
    if (m_loaded)
        this->unload();

    m_image = GenImageGradientRadial(width, height, density, inner, outer);
    m_loaded = true;
}

void graphics::RaylibImage::generateChecked(int width, int height, int checksX, int checksY, Color col1, Color col2)
{
    if (m_loaded)
        this->unload();

    m_image = GenImageChecked(width, height, checksX, checksY, col1, col2);
    m_loaded = true;
}

void graphics::RaylibImage::generateWhiteNoise(int width, int height, float factor)
{
    if (m_loaded)
        this->unload();

    m_image = GenImageWhiteNoise(width, height, factor);
    m_loaded = true;
}

void graphics::RaylibImage::generatePerlinNoise(int width, int height, int offsetX, int offsetY, float scale)
{
    if (m_loaded)
        this->unload();

    m_image = GenImagePerlinNoise(width, height, offsetX, offsetY, scale);
    m_loaded = true;
}

void graphics::RaylibImage::generateCellular(int width, int height, int tileSize)
{
    if (m_loaded)
        this->unload();

    m_image = GenImageCellular(width, height, tileSize);
    m_loaded = true;
}

void graphics::RaylibImage::generateText(int width, int height, const std::string text)
{
    if (m_loaded)
        this->unload();

    m_image = GenImageText(width, height, text.c_str());
    m_loaded = true;
}

void graphics::RaylibImage::clearBackground(Color color)
{
    if (!m_loaded)
        return;

    ImageClearBackground(&m_image, color);
}

void graphics::RaylibImage::drawPixel(int x, int y, Color color)
{
    if (!m_loaded)
        return;

    ImageDrawPixel(&m_image, x, y, color);
}

void graphics::RaylibImage::drawPixelV(Vector2 position, Color color)
{
    if (!m_loaded)
        return;

    ImageDrawPixelV(&m_image, position, color);
}

void graphics::RaylibImage::drawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color)
{
    if (!m_loaded)
        return;

    ImageDrawLine(&m_image, startPosX, startPosY, endPosX, endPosY, color);
}

void graphics::RaylibImage::drawLineV(Vector2 startPos, Vector2 endPos, Color color)
{
    if (!m_loaded)
        return;

    ImageDrawLineV(&m_image, startPos, endPos, color);
}

void graphics::RaylibImage::drawCircle(int centerX, int centerY, float radius, Color color)
{
    if (!m_loaded)
        return;

    ImageDrawCircle(&m_image, centerX, centerY, radius, color);
}

void graphics::RaylibImage::drawCircleV(Vector2 center, float radius, Color color)
{
    if (!m_loaded)
        return;

    ImageDrawCircleV(&m_image, center, radius, color);
}

void graphics::RaylibImage::drawRectangle(int posX, int posY, int width, int height, Color color)
{
    if (!m_loaded)
        return;

    ImageDrawRectangle(&m_image, posX, posY, width, height, color);
}

void graphics::RaylibImage::drawRectangleV(Vector2 position, Vector2 size, Color color)
{
    if (!m_loaded)
        return;

    ImageDrawRectangleV(&m_image, position, size, color);
}

void graphics::RaylibImage::drawRectangleRec(Rectangle rec, Color color)
{
    if (!m_loaded)
        return;

    ImageDrawRectangleRec(&m_image, rec, color);
}

void graphics::RaylibImage::drawRectangleLines(Rectangle rec, int thick, Color color)
{
    if (!m_loaded)
        return;

    ImageDrawRectangleLines(&m_image, rec, thick, color);
}

void graphics::RaylibImage::drawImage(RaylibImagePtr src, Rectangle srcRec, Rectangle dstRec, Color tint)
{

    if (!m_loaded || !src->loaded())
        return;

    ImageDraw(&m_image, src->image(), srcRec, dstRec, tint);
}

void graphics::RaylibImage::drawText(const std::string text, int posX, int posY, int fontSize, Color color)
{
    if (!m_loaded)
        return;

    ImageDrawText(&m_image, text.c_str(), posX, posY, fontSize, color);
}

bool RaylibImage::loaded() const
{
    return m_loaded;
}

void RaylibImage::unload()
{
    if (!m_loaded)
        return;

    UnloadImage(m_image);
    m_loaded = false;
}

::Image RaylibImage::image() const
{
    return m_image;
}

::Image &RaylibImage::image()
{
    return m_image;
}

int graphics::RaylibImage::width() const
{
    return m_image.width;
}

int graphics::RaylibImage::height() const
{
    return m_image.height;
}

// Path: src/gui/raylib_application.cpp
