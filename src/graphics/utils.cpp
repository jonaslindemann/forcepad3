#include <graphics/utils.h>

using namespace graphics;

void graphics::DrawEllipseLinesEx(int centerX, int centerY, float radiusH, float radiusV, float thickness, Color color)
{
    float offset = 0.0f;
    float halfThickness = thickness / 2.0f;
    float dOffset = 0.1f;

    while (offset < halfThickness)
    {
        DrawEllipseLines(centerX, centerY, radiusH + offset, radiusV + offset, DARKGRAY);
        offset += dOffset;
    }
}
