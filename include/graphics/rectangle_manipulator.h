#pragma once

#include <vector>

#include <graphics/shape.h>
#include <graphics/manipulator_handle.h>
#include <graphics/manipulator.h>

namespace graphics {

class RectangleManipulator : public Manipulator {
private:
    Vector2 m_p0{0.0f, 0.0f};
    Vector2 m_p1{0.0f, 0.0f};

    float m_handleRadius{5.0f};
    float m_handleThickness{2.0f};

public:
    RectangleManipulator();
    virtual ~RectangleManipulator();

    static std::shared_ptr<RectangleManipulator> create();

    void setP0(Vector2 p0);
    Vector2 p0() const;

    void setP1(Vector2 p1);
    Vector2 p1() const;

    void setHandleRadius(float radius);
    float handleRadius() const;

    void setHandleThickness(float thickness);
    float handleThickness() const;

    Vector2 upperLeft();
    Vector2 lowerRight();

    void updateHandles();

    virtual void doDraw() override;
    virtual void doDrawOutline() override;
    virtual void doDrawHover() override;
    virtual bool doIsInside(float x, float y) override;
    virtual void doUpdate(ManipulatorHandle *handle) override;
};

using RectangleManipulatorPtr = std::shared_ptr<RectangleManipulator>;

} // namespace graphics
