#pragma once

#include <graphics/shape.h>

namespace graphics {

class Manipulator;

class ManipulatorHandle : public Shape {
private:
    Vector2 m_position;
    float m_radius{5.0f};
    float m_thickness{2.0f};
    Manipulator *m_manipulator{nullptr};

public:
    ManipulatorHandle() = default;
    virtual ~ManipulatorHandle() = default;

    static std::shared_ptr<ManipulatorHandle> create();

    void setPosition(Vector2 position);
    Vector2 position() const;

    void setRadius(float radius);
    float radius() const;

    void setThickness(float thickness);
    float thickness() const;

    void setManipulator(Manipulator *manipulator);
    Manipulator *manipulator() const;

    virtual void doDraw() override;
    virtual void doDrawOutline() override;
    virtual void doDrawHover() override;
    virtual bool doIsInside(float x, float y) override;
    virtual void doMove(float x, float y) override;
    virtual BoundingBox doUpdateBoundingBox() override;
    virtual void doUpdateFromBounds(const BoundingBox &bounds) override;
};

using ManipulatorHandlePtr = std::shared_ptr<ManipulatorHandle>;

} // namespace graphics
