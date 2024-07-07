#include <graphics/drawing.h>

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
    m_renderLayers.push_back(RaylibRenderTexture::create());
    m_renderLayers.back()->load(m_width, m_height);

    LayerProperties prop;
    prop.setName("Layer " + std::to_string(m_renderLayers.size()));
    m_layerProperties.push_back(prop);
}

void Drawing::beginDraw()
{
    currentLayer()->beginDraw();
}

void Drawing::draw()
{
    for (auto i = 0; i < m_renderLayers.size(); i++)
    {
        if (m_layerProperties[i].visible())
            m_renderLayers[i]->draw();
    }
}

void Drawing::endDraw()
{
    currentLayer()->endDraw();
}

void Drawing::setCurrentLayer(int index)
{
    m_currentLayer = index;
}

RaylibRenderTexturePtr Drawing::currentLayer()
{
    if (m_currentLayer < 0 || m_currentLayer >= m_renderLayers.size())
    {
        return RaylibRenderTexturePtr();
    }
    else
        return m_renderLayers[m_currentLayer];
}

RaylibRenderTexturePtr Drawing::layer(int index)
{
    if (index < 0 || index >= m_renderLayers.size())
    {
        return RaylibRenderTexturePtr();
    }
    else
        return m_renderLayers[index];
}

int graphics::Drawing::currentLayerIndex() const
{
    return m_currentLayer;
}

LayerProperties &graphics::Drawing::layerProp(int index)
{
    // TODO: insert return statement here
    return m_layerProperties[index];
}

size_t Drawing::layerCount() const
{
    return m_renderLayers.size();
}

int Drawing::width() const
{
    return m_width;
}

int Drawing::height() const
{
    return m_height;
}

void LayerProperties::setPosition(Vector2 position)
{
    m_position = position;
}

Vector2 LayerProperties::position() const
{
    return m_position;
}

void LayerProperties::setScale(float scale)
{
    m_scale = scale;
}

float LayerProperties::scale() const
{
    return m_scale;
}

void LayerProperties::setVisible(bool visible)
{
    m_visible = visible;
}

bool LayerProperties::visible() const
{
    return m_visible;
}

void graphics::LayerProperties::setName(const std::string &name)
{
    m_name = name;
}

std::string graphics::LayerProperties::name() const
{
    return m_name;
}

void graphics::LayerProperties::setTint(Color tint)
{
    m_tint = tint;
}

Color graphics::LayerProperties::tint() const
{
    return m_tint;
}
