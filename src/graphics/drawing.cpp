#include <graphics/drawing.h>

#include <graphics/rectangle.h>
#include <graphics/ellipse.h>

#include <cmath>
#include <ranges>

using namespace graphics;

Drawing::Drawing(int width, int height) : m_width(width), m_height(height), m_currentLayer(0)
{
    addLayer();
}

std::shared_ptr<Drawing> graphics::Drawing::create(int width, int height)
{
    return std::make_shared<Drawing>(width, height);
}

void Drawing::addLayer()
{
    auto layer = Layer::create(m_width, m_height, this);
    m_layers.push_back(layer);
    layer->setName("Layer " + std::to_string(m_layers.size()));
}

void graphics::Drawing::updateMouse(float x, float y)
{
    m_mouseX = x;
    m_mouseY = y;
}

void graphics::Drawing::updateCurrentShape(Shape *shape)
{
    m_currentShape = shape;
}

Shape *graphics::Drawing::currentShape()
{
    return m_currentShape;
}

void Drawing::beginDraw()
{
    currentLayer()->texture()->beginDraw();
}

void Drawing::draw()
{
    if (m_currentShape != nullptr)
        m_currentShape->setHover(false);

    m_currentShape = nullptr;

    for (auto &layer : m_layers | std::views::reverse)
    {
        if (layer->visible())
        {
            layer->updateMouse(mouseX(), mouseY());
            layer->checkHover();
        }
    }

    for (auto &layer : m_layers)
    {
        if (layer->visible())
        {
            layer->draw();
        }
    }

    if (m_currentShape != nullptr)
        m_currentShape->setHover(false);

    m_currentShape = nullptr;
}

void Drawing::endDraw()
{
    currentLayer()->texture()->endDraw();
}

void Drawing::setCurrentLayer(int index)
{
    m_currentLayer = index;
}

LayerPtr Drawing::currentLayer()
{
    if (m_currentLayer < 0 || m_currentLayer >= m_layers.size())
    {
        return LayerPtr();
    }
    else
        return m_layers[m_currentLayer];
}

LayerPtr Drawing::layer(int index)
{
    if (index < 0 || index >= m_layers.size())
    {
        return LayerPtr();
    }
    else
        return m_layers[index];
}

int graphics::Drawing::currentLayerIndex() const
{
    return m_currentLayer;
}

size_t Drawing::layerCount() const
{
    return m_layers.size();
}

int Drawing::width() const
{
    return m_width;
}

int Drawing::height() const
{
    return m_height;
}

float graphics::Drawing::mouseX() const
{
    return m_mouseX;
}

float graphics::Drawing::mouseY() const
{
    return m_mouseY;
}

graphics::Layer::Layer(int width, int height, Drawing *drawing) : m_drawing(drawing)
{
    m_renderTexture = std::make_shared<RaylibRenderTexture>();
    m_renderTexture->load(width, height);

    for (auto i = 0; i < 20; i++)
    {
        auto choice = GetRandomValue(0, 1);

        if (choice == 0)
        {
            auto ellipse = Ellipse::create();
            ellipse->setOutline(false);
            ellipse->setOutlineWidth(2.0f);
            ellipse->setP0(Vector2{float(GetRandomValue(0, width)), float(GetRandomValue(0, height))});
            ellipse->setRadiusX(float(GetRandomValue(0, width) * 0.1));
            ellipse->setRadiusY(float(GetRandomValue(0, height) * 0.1));
            ellipse->setFillColor(Color{(unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255),
                                        (unsigned char)GetRandomValue(0, 255), 255});
            ellipse->setStrokeWidth(2.0f);
            this->addShape(ellipse);
        }
        else if (choice == 1)
        {
            auto rect = Rectangle::create();
            rect->setOutline(false);
            rect->setOutlineWidth(2.0f);
            rect->setP0(Vector2{float(GetRandomValue(0, width)), float(GetRandomValue(0, height))});
            rect->setSize(Vector2{float(GetRandomValue(0, width) * 0.1), float(GetRandomValue(0, height) * 0.1)});
            rect->setFillColor(Color{(unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255),
                                     (unsigned char)GetRandomValue(0, 255), 255});
            rect->setStrokeWidth(2.0f);
            this->addShape(rect);
        }
    }
}

std::shared_ptr<Layer> graphics::Layer::create(int width, int height, Drawing *drawing)
{
    return std::make_shared<Layer>(width, height, drawing);
}

void graphics::Layer::setPosition(Vector2 position)
{
    m_position = position;
}

Vector2 graphics::Layer::position() const
{
    return m_position;
}

void graphics::Layer::setScale(float scale)
{
    m_scale = scale;
}

float graphics::Layer::scale() const
{
    return m_scale;
}

void graphics::Layer::setVisible(bool visible)
{
    m_visible = visible;
}

bool graphics::Layer::visible() const
{
    return m_visible;
}

void graphics::Layer::setName(const std::string &name)
{
    m_name = name;
}

std::string graphics::Layer::name() const
{
    return m_name;
}

void graphics::Layer::setTint(Color tint)
{
    m_tint = tint;
}

Color graphics::Layer::tint() const
{
    return m_tint;
}

RaylibRenderTexturePtr graphics::Layer::texture()
{
    return m_renderTexture;
}

Drawing *graphics::Layer::drawing()
{
    return m_drawing;
}

void graphics::Layer::updateMouse(float x, float y)
{
    m_mouseX = x;
    m_mouseY = y;
}

void graphics::Layer::beginDraw()
{
    m_renderTexture->beginDraw();
}

void graphics::Layer::endDraw()
{
    m_renderTexture->endDraw();
}

void graphics::Layer::addShape(std::shared_ptr<Shape> shape)
{
    m_shapes.push_back(shape);
}

void graphics::Layer::draw()
{
    m_renderTexture->draw(0, 0, m_tint);

    for (auto &shape : m_shapes)
    {
        shape->draw();
    }
}

void graphics::Layer::checkHover()
{
    auto currentShape = m_drawing->currentShape();

    for (auto &shape : m_shapes | std::views::reverse)
    {
        if (shape->isInside(mouseX(), mouseY()) && (currentShape == nullptr))
        {
            shape->setHover(true);

            if (currentShape != nullptr)
                currentShape->setHover(false);

            m_drawing->updateCurrentShape(shape.get());
            currentShape = m_drawing->currentShape();
        }
        else
        {
            shape->setHover(false);
        }
    }
}

float graphics::Layer::mouseX() const
{
    return m_mouseX;
}

float graphics::Layer::mouseY() const
{
    return m_mouseY;
}
