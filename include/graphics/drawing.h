#pragma once

#include <memory>
#include <vector>
#include <string>

#include <raylib.h>

#include <graphics/raylib_render_texture.h>

namespace graphics {

class LayerProperties {
private:
    Vector2 m_position{0.0f, 0.0f};
    float m_scale{1.0};
    bool m_visible{true};
    std::string m_name;
    Color m_tint{WHITE};

public:
    LayerProperties() = default;

    void setPosition(Vector2 position);
    Vector2 position() const;

    void setScale(float scale);
    float scale() const;

    void setVisible(bool visible);
    bool visible() const;

    void setName(const std::string &name);
    std::string name() const;

    void setTint(Color tint);
    Color tint() const;
};

class Drawing {
private:
    std::vector<RaylibRenderTexturePtr> m_renderLayers;
    std::vector<LayerProperties> m_layerProperties;
    int m_currentLayer{0};
    int m_width{-1};
    int m_height{-1};

public:
    Drawing(int width, int height);

    static std::shared_ptr<Drawing> create(int width, int height);

    void addLayer();

    void beginDraw();
    void draw();
    void endDraw();

    void setCurrentLayer(int index);

    RaylibRenderTexturePtr currentLayer();
    RaylibRenderTexturePtr layer(int index);
    int currentLayerIndex() const;

    LayerProperties &layerProp(int index);

    size_t layerCount() const;
    int width() const;
    int height() const;
};

using DrawingPtr = std::shared_ptr<Drawing>;

} // namespace graphics
