#include <graphics/manipulator.h>

using namespace graphics;

std::shared_ptr<Manipulator> graphics::Manipulator::create()
{
    return std::make_shared<Manipulator>();
}

void graphics::Manipulator::addHandle(float x, float y)
{
    auto handle = ManipulatorHandle::create();
    handle->setManipulator(this);
    handle->setPosition(Vector2(x, y));
    addHandle(handle);
}

void graphics::Manipulator::addHandle(Vector2 position)
{
    auto handle = ManipulatorHandle::create();
    handle->setManipulator(this);
    handle->setPosition(position);
    addHandle(handle);
}

void graphics::Manipulator::addHandle(ManipulatorHandlePtr handle)
{
    handle->setManipulator(this);
    m_handles.push_back(handle);
}

void graphics::Manipulator::addHandles(int count)
{
    for (int i = 0; i < count; i++)
    {
        auto handle = ManipulatorHandle::create();
        handle->setManipulator(this);
        addHandle(handle);
    }
}

void graphics::Manipulator::removeHandle(ManipulatorHandlePtr handle)
{
    auto it = std::find(m_handles.begin(), m_handles.end(), handle);
    if (it != m_handles.end())
    {
        m_handles.erase(it);
    }
}

void graphics::Manipulator::clearHandles()
{
    m_handles.clear();
}

std::vector<ManipulatorHandlePtr> graphics::Manipulator::handles() const
{
    return m_handles;
}

void graphics::Manipulator::update(ManipulatorHandle *handle)
{
    doUpdate(handle);
}

void graphics::Manipulator::doDraw()
{
    for (auto &handle : m_handles)
    {
        handle->draw();
    }
}

void graphics::Manipulator::doDrawOutline()
{}

void graphics::Manipulator::doDrawHover()
{}

bool graphics::Manipulator::doIsInside(float x, float y)
{
    return false;
}

void graphics::Manipulator::doMove(float x, float y)
{}

void graphics::Manipulator::doUpdate(ManipulatorHandle *handle)
{}

graphics::BoundingBox graphics::Manipulator::doUpdateBoundingBox()
{
    return BoundingBox();
}

void graphics::Manipulator::doUpdateFromBounds(const BoundingBox &bounds)
{}
