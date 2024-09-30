#pragma once

#include <memory>
#include <vector>
#include <string>

#include <raylib.h>

#include <graphics/raylib_render_texture.h>
#include <graphics/shape.h>
#include <graphics/manipulator_handle.h>
#include <graphics/rectangle_manipulator.h>

namespace graphics {

class Drawing;

class Layer {
private:
    RaylibRenderTexturePtr m_renderTexture{nullptr};
    std::vector<std::shared_ptr<Shape>> m_shapes;
    Vector2 m_position{0.0f, 0.0f};
    float m_scale{1.0};
    bool m_visible{true};
    std::string m_name;
    Color m_tint{WHITE};

    Drawing *m_drawing;

    float m_mouseX{-1.0f};
    float m_mouseY{-1.0f};

public:
    Layer(int width, int height, Drawing *drawing);

    static std::shared_ptr<Layer> create(int width, int height, Drawing *drawing);

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

    RaylibRenderTexturePtr texture();

    Drawing *drawing();

    void updateMouse(float x, float y);

    void beginDraw();
    void endDraw();

    void addShape(std::shared_ptr<Shape> shape);

    void removeShape(Shape *shape);

    void draw();
    void checkHover();
    void checkHandle();

    Shape *shapeAt(float x, float y);

    float mouseX() const;
    float mouseY() const;
};

using LayerPtr = std::shared_ptr<Layer>;

}; // namespace graphics
