#pragma once

#include <memory>
#include <vector>
#include <string>

#include <raylib.h>

#include <graphics/raylib_render_texture.h>
#include <graphics/shape.h>
#include <graphics/manipulator_handle.h>
#include <graphics/rectangle_manipulator.h>
#include <graphics/layer.h>

namespace graphics {

class Drawing {
private:
    std::vector<LayerPtr> m_layers;
    LayerPtr m_manipulationLayer{nullptr};
    int m_currentLayer{0};
    int m_width{-1};
    int m_height{-1};
    float m_mouseX{-1.0f};
    float m_mouseY{-1.0f};

    Shape *m_currentShape{nullptr};
    ManipulatorHandle *m_currentHandle{nullptr};
    RectangleManipulatorPtr m_rectangleManipulator{nullptr};

    ShapePtr m_newShape{nullptr};

    std::vector<Shape *> m_selectedShapes;

public:
    Drawing(int width, int height);

    static std::shared_ptr<Drawing> create(int width, int height);

    void addLayer();

    void updateMouse(float x, float y);
    void updateCurrentShape(Shape *shape);
    void updateCurrentHandle(ManipulatorHandle *handle);

    Shape *currentShape();
    ManipulatorHandle *currentHandle();
    RectangleManipulator *rectangleManipulator();

    void beginDraw();
    void draw();
    void endDraw();

    void setCurrentLayer(int index);

    void setNewShape(ShapePtr shape);
    ShapePtr newShape();
    void clearNewShape();

    LayerPtr currentLayer();
    LayerPtr layer(int index);
    int currentLayerIndex() const;

    size_t layerCount() const;
    int width() const;
    int height() const;

    Shape *shapeAt(float x, float y);

    void select();
    void deselect();
    void clearSelection();
    void updateBoundsSelection();
    void updateSelectionBounds();

    void deleteSelected();

    Shape *selectedShape();

    float mouseX() const;
    float mouseY() const;
};

using DrawingPtr = std::shared_ptr<Drawing>;

} // namespace graphics
