#pragma once
#include <graphics/shape.h>

namespace graphics {

class RectangleManipulator : public Shape {
private:
    Vector2 m_p0;
    Vector2 m_p1;

    float m_handleRadius{5.0f};
    float m_handleThickness{2.0f};

public:
    RectangleManipulator() = default;
    virtual ~RectangleManipulator() = default;

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

    virtual void doDraw() override;
    virtual void doDrawOutline() override;
    virtual void doDrawHover() override;
    virtual bool doIsInside(float x, float y) override;
};

using RectangleManipulatorPtr = std::shared_ptr<RectangleManipulator>;

} // namespace graphics
