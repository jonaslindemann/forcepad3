#pragma once

#include <string>
#include <memory>

#include "raylib.h"

namespace graphics {

class RaylibImage;

typedef std::shared_ptr<RaylibImage> RaylibImagePtr;

class RaylibImage {
private:
    ::Image m_image;
    bool m_loaded{false};

public:
    RaylibImage();

    static std::shared_ptr<RaylibImage> create();

    void loadFromFile(std::string filename);
    void generateColor(int width, int height, Color color);
    void generateGradientLinear(int width, int height, int direction, Color start, Color end);
    void generateGradientRadial(int width, int height, float density, Color inner, Color outer);
    void generateChecked(int width, int height, int checksX, int checksY, Color col1, Color col2);
    void generateWhiteNoise(int width, int height, float factor);
    void generatePerlinNoise(int width, int height, int offsetX, int offsetY, float scale);
    void generateCellular(int width, int height, int tileSize);
    void generateText(int width, int height, const std::string text);

    void clearBackground(Color color);
    void drawPixel(int x, int y, Color color);
    void drawPixelV(Vector2 position, Color color);
    void drawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);
    void drawLineV(Vector2 startPos, Vector2 endPos, Color color);
    void drawCircle(int centerX, int centerY, float radius, Color color);
    void drawCircleV(Vector2 center, float radius, Color color);
    void drawRectangle(int posX, int posY, int width, int height, Color color);
    void drawRectangleV(Vector2 position, Vector2 size, Color color);
    void drawRectangleRec(Rectangle rec, Color color);
    void drawRectangleLines(Rectangle rec, int thick, Color color);
    void drawImage(RaylibImagePtr src, Rectangle srcRec, Rectangle dstRec, Color tint);
    void drawText(const std::string text, int posX, int posY, int fontSize, Color color);

    bool loaded() const;
    void unload();

    ::Image image() const;
    ::Image &image();

    int width() const;
    int height() const;
};

} // namespace graphics
