#include <graphics/layer.h>

#include <graphics/rectangle.h>
#include <graphics/ellipse.h>
#include <graphics/rectangle_manipulator.h>
#include <graphics/drawing.h>

#include <cmath>
#include <ranges>

using namespace graphics;

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
        shape->draw();
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
