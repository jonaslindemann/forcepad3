#include <graphics/drawing.h>

#include <graphics/rectangle.h>
#include <graphics/ellipse.h>
#include <graphics/rectangle_manipulator.h>

#include <cmath>
#include <ranges>

using namespace graphics;

Drawing::Drawing(int width, int height)
    : m_width(width), m_height(height), m_currentLayer(0), m_mouseX(-1.0f), m_mouseY(-1.0f), m_currentShape(nullptr),
      m_newShape(nullptr), m_manipulationLayer(nullptr), m_currentHandle(nullptr), m_rectangleManipulator(nullptr)
{
    addLayer();
    m_manipulationLayer = Layer::create(width, height, this);
    m_rectangleManipulator = RectangleManipulator::create();
    m_rectangleManipulator->setVisible(false);
    m_manipulationLayer->addShape(m_rectangleManipulator);
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

void graphics::Drawing::updateCurrentHandle(ManipulatorHandle *handle)
{
    m_currentHandle = handle;
}

Shape *graphics::Drawing::currentShape()
{
    return m_currentShape;
}

ManipulatorHandle *graphics::Drawing::currentHandle()
{
    return m_currentHandle;
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

    m_manipulationLayer->updateMouse(mouseX(), mouseY());

    for (auto &layer : m_layers)
    {
        if (layer->visible())
        {
            layer->draw();
        }
    }

    m_manipulationLayer->draw();
    m_manipulationLayer->checkHandle();

    if (m_currentShape != nullptr)
        m_currentShape->setHover(false);

    m_currentShape = nullptr;

    if (m_newShape != nullptr)
        m_newShape->draw();
}

void Drawing::endDraw()
{
    currentLayer()->texture()->endDraw();
}

void Drawing::setCurrentLayer(int index)
{
    m_currentLayer = index;
}

void graphics::Drawing::setNewShape(ShapePtr shape)
{
    m_newShape = shape;
}

ShapePtr graphics::Drawing::newShape()
{
    return m_newShape;
}

void graphics::Drawing::clearNewShape()
{
    m_newShape = nullptr;
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

Shape *graphics::Drawing::shapeAt(float x, float y)
{
    for (auto &layer : m_layers | std::views::reverse)
    {
        if (auto shape = layer->shapeAt(x, y))
        {
            return shape;
        }
    }

    return nullptr;
}

void graphics::Drawing::select()
{
    this->clearSelection();

    auto selectedShape = this->shapeAt(mouseX(), mouseY());

    std::printf("Selected shape: %p\n", selectedShape);

    if (selectedShape != nullptr)
        m_selectedShapes.push_back(selectedShape);

    std::printf("Selected shapes: %zu\n", m_selectedShapes.size());

    if (m_selectedShapes.size() == 1)
    {
        m_rectangleManipulator->setVisible(true);
        m_rectangleManipulator->setP0(
            Vector2(m_selectedShapes[0]->boundingBox().left(), m_selectedShapes[0]->boundingBox().top()));
        m_rectangleManipulator->setP1(
            Vector2(m_selectedShapes[0]->boundingBox().right(), m_selectedShapes[0]->boundingBox().bottom()));
    }
    else
    {
        m_rectangleManipulator->setVisible(false);
    }
}

void graphics::Drawing::deselect()
{}

void graphics::Drawing::clearSelection()
{
    m_selectedShapes.clear();
}

void graphics::Drawing::updateBoundsSelection()
{
    if (m_selectedShapes.size() == 1)
    {
        m_selectedShapes[0]->updateFromBounds(m_rectangleManipulator->boundingBox());
    }
}

void graphics::Drawing::deleteSelected()
{
    for (auto &shape : m_selectedShapes)
    {
        for (auto &layer : m_layers)
        {
            layer->removeShape(m_selectedShapes[0]);
        }
    }

    m_selectedShapes.clear();
    m_rectangleManipulator->setVisible(false);
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

void graphics::Layer::removeShape(Shape *shape)
{
    m_shapes.erase(std::remove_if(m_shapes.begin(), m_shapes.end(),
                                  [shape](const std::shared_ptr<Shape> &s) { return s.get() == shape; }),
                   m_shapes.end());
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

void graphics::Layer::checkHandle()
{
    ManipulatorHandle *currentHandle = nullptr;
    m_drawing->updateCurrentHandle(nullptr);

    for (auto &shape : m_shapes | std::views::reverse)
    {
        if (auto manipulator = std::dynamic_pointer_cast<Manipulator>(shape))
        {
            for (auto &handle : manipulator->handles())
            {
                if (handle->isInside(mouseX(), mouseY()) && (currentHandle == nullptr))
                {
                    m_drawing->updateCurrentHandle(handle.get());
                    currentHandle = m_drawing->currentHandle();
                }
            }
        }
    }
}

Shape *graphics::Layer::shapeAt(float x, float y)
{
    for (auto &shape : m_shapes | std::views::reverse)
    {
        if (shape->isInside(x, y))
        {
            return shape.get();
        }
    }

    return nullptr;
}

float graphics::Layer::mouseX() const
{
    return m_mouseX;
}

float graphics::Layer::mouseY() const
{
    return m_mouseY;
}
