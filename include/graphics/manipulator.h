#pragma once
#include <graphics/shape.h>
#include <graphics/manipulator_handle.h>

#include <vector>

namespace graphics {

class Manipulator : public Shape {
private:
    std::vector<ManipulatorHandlePtr> m_handles;

public:
    Manipulator() = default;
    virtual ~Manipulator() = default;

    static std::shared_ptr<Manipulator> create();

    void addHandle(float x, float y);
    void addHandle(Vector2 position);
    void addHandle(ManipulatorHandlePtr handle);
    void addHandles(int count);
    void removeHandle(ManipulatorHandlePtr handle);
    void clearHandles();
    std::vector<ManipulatorHandlePtr> handles() const;
    void update(ManipulatorHandle *handle);

    virtual void doDraw() override;
    virtual void doDrawOutline() override;
    virtual void doDrawHover() override;
    virtual bool doIsInside(float x, float y) override;
    virtual void doMove(float x, float y) override;
    virtual void doUpdate(ManipulatorHandle *handle);
};

} // namespace graphics
