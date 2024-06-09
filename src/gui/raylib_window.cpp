#include "gui/raylib_window.h"

#include "gui/raylib_application.h"

using namespace gui;

RaylibWindow::RaylibWindow(int width, int height, std::string title)
    : m_width(width), m_height(height), m_title(title), m_app(nullptr)
{}

void gui::RaylibWindow::setApplication(RaylibApplication *app)
{
    m_app = app;
}

gui::RaylibApplication *gui::RaylibWindow::application() const
{
    return m_app;
}

void gui::RaylibWindow::setState(unsigned int flags)
{
    SetWindowState(flags);
}

void gui::RaylibWindow::setWidth(int width)
{
    m_width = width;
}

void gui::RaylibWindow::setHeight(int height)
{
    m_height = height;
}

int gui::RaylibWindow::width() const
{
    return m_width;
}

int gui::RaylibWindow::height() const
{
    return m_height;
}

float gui::RaylibWindow::widthF() const
{
    return float(m_width);
}

float gui::RaylibWindow::heightF() const
{
    return float(m_height);
}

std::string gui::RaylibWindow::title() const
{
    return m_title;
}

int gui::RaylibWindow::screenWidth() const
{
    return GetScreenWidth();
}

int gui::RaylibWindow::screenHeight() const
{
    return GetScreenHeight();
}

int gui::RaylibWindow::monitorWidth() const
{
    return GetMonitorWidth(0);
}

int gui::RaylibWindow::monitorHeight() const
{
    return GetMonitorHeight(0);
}

float gui::RaylibWindow::mouseX() const
{
    auto pos = GetMousePosition();
    return pos.x;
}

float gui::RaylibWindow::mouseY() const
{
    auto pos = GetMousePosition();
    return pos.y;
}

gui::MouseButton gui::RaylibWindow::currentMouseButton() const
{
    MouseButton button = MouseButton::NO_BUTTON;

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        button = MouseButton::LEFT_BUTTON;
    else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
        button = MouseButton::RIGHT_BUTTON;
    else if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON))
        button = MouseButton::MIDDLE_BUTTON;

    return button;
}

void gui::RaylibWindow::onInit()
{
    InitWindow(m_width, m_height, m_title.c_str());
    SetWindowState(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
}

void gui::RaylibWindow::onSetup()
{}

void gui::RaylibWindow::onClear()
{}

void gui::RaylibWindow::onUpdate()
{}

void gui::RaylibWindow::onDraw()
{}

void gui::RaylibWindow::onResize(int width, int height)
{}

void gui::RaylibWindow::onKeyPressed(int key)
{}

void gui::RaylibWindow::onMousePressed(MouseButton button, float x, float y)
{}

void gui::RaylibWindow::onMouseDown(MouseButton button, float x, float y)
{}

void gui::RaylibWindow::onMouseMove(float x, float y)
{}

void gui::RaylibWindow::onMouseReleased(MouseButton button, float x, float y)
{}

void gui::RaylibWindow::onClose()
{}
