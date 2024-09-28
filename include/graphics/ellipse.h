#pragma once

#include <memory>

#include "raylib.h"

#include <graphics/shape.h>

namespace graphics {

class Ellipse : public Shape {
private:
    Vector2 m_p0{0.0f, 0.0f};
    float m_radiusX{50.0f};
    float m_radiusY{50.0f};

public:
    Ellipse() = default;
    ~Ellipse() = default;

    static std::shared_ptr<Ellipse> create();

    void setP0(Vector2 p0);
    Vector2 p0() const;

    void setRadiusX(float radiusX);
    float radiusX() const;

    void setRadiusY(float radiusY);
    float radiusY() const;

    virtual void doDraw() override;
    virtual void doDrawOutline() override;
    virtual void doDrawHover() override;
    virtual bool doIsInside(float x, float y) override;
    virtual void doMove(float x, float y) override;
    virtual BoundingBox doUpdateBoundingBox() override;
    virtual void doUpdateFromBounds(const BoundingBox &bounds) override;
};

using EllipsePtr = std::shared_ptr<Ellipse>;

}; // namespace graphics
