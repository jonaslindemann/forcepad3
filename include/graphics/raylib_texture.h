#pragma once

#include "raylib.h"

#include "graphics/raylib_image.h"

namespace graphics {

class RaylibTexture {
private:
    Texture2D m_texture;
    bool m_loaded = false;
    int m_width = 0;
    int m_height = 0;

public:
    RaylibTexture();
    ~RaylibTexture();

    static std::shared_ptr<RaylibTexture> create();

    void loadFromImage(RaylibImagePtr image);
    void updateFromImage(RaylibImagePtr image);

    void unload();
    bool isLoaded() const;

    Texture2D texture() const;
    Texture2D &texture();
    Texture2D *texturePtr();

    int width() const;
    int height() const;
    float widthF() const;
    float heightF() const;
};

using RaylibTexturePtr = std::shared_ptr<RaylibTexture>;

} // namespace graphics
