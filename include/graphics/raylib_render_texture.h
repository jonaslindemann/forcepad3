#pragma once

#include <memory>

#include "raylib.h"

namespace graphics {

class RaylibRenderTexture {
private:
    RenderTexture2D m_texture;
    bool m_loaded = false;
    int m_width = 0;
    int m_height = 0;
    Vector2 m_position;
    float m_scale;

public:
    RaylibRenderTexture();
    ~RaylibRenderTexture();

    static std::shared_ptr<RaylibRenderTexture> create();

    void load(int width, int height);
    void unload();
    bool isLoaded() const;

    RenderTexture2D texture() const;
    RenderTexture2D &texture();

    void beginDraw();
    void endDraw();

    void draw(int x, int y, Color tint = WHITE);
    void draw();

    int width() const;
    int height() const;
    float widthF() const;
    float heightF() const;

    void setPosition(Vector2 position);
    Vector2 position() const;

    void setScale(float scale);
    float scale() const;
};

using RaylibRenderTexturePtr = std::shared_ptr<RaylibRenderTexture>;

} // namespace graphics
