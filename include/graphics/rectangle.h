#pragma once

#include <memory>

#include "raylib.h"

#include <graphics/shape.h>

namespace graphics {

class Rectangle : public Shape {
private:
    Vector2 m_p0{0.0f, 0.0f};
    Vector2 m_p1{0.0f, 0.0f};

public:
    Rectangle() = default;
    ~Rectangle() = default;

    static std::shared_ptr<Rectangle> create();

    void setP0(Vector2 p0);
    Vector2 p0() const;

    void setP1(Vector2 p1);
    Vector2 p1() const;

    void setSize(Vector2 size);
    Vector2 size() const;

    Vector2 upperLeft();
    Vector2 lowerRight();

    virtual void doDraw() override;
    virtual void doDrawOutline() override;
    virtual void doDrawHover() override;
    virtual bool doIsInside(float x, float y) override;
    virtual void doMove(float x, float y) override;
};

using RectanglePtr = std::shared_ptr<Rectangle>;

}; // namespace graphics
