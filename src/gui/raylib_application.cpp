#include "gui/raylib_application.h"

using namespace gui;

RaylibApplication::RaylibApplication(RaylibWindowPtr window)
    : m_window(window), m_mousePos({0, 0}), m_lastMousePos({0, 0}), m_currentMouseButton(MouseButton::NO_BUTTON),
      m_lastMouseButton(MouseButton::NO_BUTTON)
{
    m_window->setApplication(this);
}

std::unique_ptr<RaylibApplication> RaylibApplication::create(RaylibWindowPtr window)
{
    return std::make_unique<RaylibApplication>(window);
}

void gui::RaylibApplication::setWindow(RaylibWindowPtr window)
{
    m_window = window;
}

void gui::RaylibApplication::setConfigFlags(unsigned int flags)
{
    SetConfigFlags(flags);
}

void gui::RaylibApplication::setTargetFPS(int fps)
{
    SetTargetFPS(fps);
}

void RaylibApplication::loop()
{
    if (m_window == nullptr)
        return;

    m_window->onInit();
    m_window->onSetup();

    m_mousePos = GetMousePosition();
    m_lastMousePos = m_mousePos;

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        if (IsWindowResized())
        {
            m_window->setWidth(GetRenderWidth());
            m_window->setHeight(GetRenderHeight());
            m_window->onResize(m_window->width(), m_window->height());
        }

        // Check keyboard

        auto keycode = GetKeyPressed();

        while (keycode != 0)
        {
            m_window->onKeyPressed(keycode);
            keycode = GetKeyPressed();
        }

        // Check mouse

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            auto mousePos = GetMousePosition();
            m_currentMouseButton = MouseButton::LEFT_BUTTON;
            m_window->onMouseDown(MouseButton::LEFT_BUTTON, mousePos.x, mousePos.y);
        }

        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
        {
            auto mousePos = GetMousePosition();
            m_currentMouseButton = MouseButton::RIGHT_BUTTON;
            m_window->onMouseDown(MouseButton::RIGHT_BUTTON, mousePos.x, mousePos.y);
        }

        if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON))
        {
            auto mousePos = GetMousePosition();
            m_currentMouseButton = MouseButton::MIDDLE_BUTTON;
            m_window->onMouseDown(MouseButton::MIDDLE_BUTTON, mousePos.x, mousePos.y);
        }

        if (noMouseButtonDown())
        {
            if (m_currentMouseButton == MouseButton::LEFT_BUTTON)
            {
                auto mousePos = GetMousePosition();
                m_window->onMouseReleased(MouseButton::LEFT_BUTTON, mousePos.x, mousePos.y);
                m_window->onMousePressed(MouseButton::LEFT_BUTTON, mousePos.x, mousePos.y);
                m_lastMouseButton = MouseButton::LEFT_BUTTON;
                m_currentMouseButton = MouseButton::NO_BUTTON;
            }
            if (m_currentMouseButton == MouseButton::RIGHT_BUTTON)
            {
                auto mousePos = GetMousePosition();
                m_window->onMouseReleased(MouseButton::RIGHT_BUTTON, mousePos.x, mousePos.y);
                m_window->onMousePressed(MouseButton::RIGHT_BUTTON, mousePos.x, mousePos.y);
                m_lastMouseButton = MouseButton::RIGHT_BUTTON;
                m_currentMouseButton = MouseButton::NO_BUTTON;
            }
            if (m_currentMouseButton == MouseButton::MIDDLE_BUTTON)
            {
                auto mousePos = GetMousePosition();
                m_window->onMouseReleased(MouseButton::MIDDLE_BUTTON, mousePos.x, mousePos.y);
                m_window->onMousePressed(MouseButton::MIDDLE_BUTTON, mousePos.x, mousePos.y);
                m_lastMouseButton = MouseButton::MIDDLE_BUTTON;
                m_currentMouseButton = MouseButton::NO_BUTTON;
            }
        }

        // Check mouse move

        m_mousePos = GetMousePosition();

        if (m_mousePos.x != m_lastMousePos.x || m_mousePos.y != m_lastMousePos.y)
            m_window->onMouseMove(m_mousePos.x, m_mousePos.y);

        m_lastMousePos = m_mousePos;

        // Update and draw

        m_window->onUpdate();
        m_window->onClear();
        BeginDrawing();
        m_window->onDraw();
        EndDrawing();
    }

    m_window->onClose();

    CloseWindow();
}

bool gui::RaylibApplication::anyMouseButtonDown() const
{
    return IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_RIGHT_BUTTON) ||
           IsMouseButtonDown(MOUSE_MIDDLE_BUTTON);
}

bool gui::RaylibApplication::noMouseButtonDown() const
{
    return !IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !IsMouseButtonDown(MOUSE_RIGHT_BUTTON) &&
           !IsMouseButtonDown(MOUSE_MIDDLE_BUTTON);
}

gui::MouseButton gui::RaylibApplication::currentMouseButton() const
{
    return m_currentMouseButton;
}

gui::MouseButton gui::RaylibApplication::lastMouseButton() const
{
    return m_lastMouseButton;
}
