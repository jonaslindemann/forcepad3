#pragma once
#include <graphics/shape.h>

#include <memory>

namespace graphics {

class Line : public Shape {
private:
    Vector2 m_p0{0.0f, 0.0f};
    Vector2 m_p1{0.0f, 0.0f};

public:
    Line() = default;
    ~Line() = default;

    static std::shared_ptr<Line> create();

    void setP0(Vector2 p0);
    Vector2 p0() const;

    void setP1(Vector2 p1);
    Vector2 p1() const;

    virtual void doDraw() override;
    virtual void doDrawOutline() override;
    virtual void doDrawHover() override;
    virtual bool doIsInside(float x, float y) override;
    virtual void doMove(float x, float y) override;
};

using LinePtr = std::shared_ptr<Line>;

} // namespace graphics
