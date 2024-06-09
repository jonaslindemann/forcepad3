#pragma once

#include "raylib.h"
#include "raylib_window.h"

namespace gui {

class RaylibApplication {
private:
    RaylibWindowPtr m_window;

    Vector2 m_mousePos;
    Vector2 m_lastMousePos;

    MouseButton m_lastMouseButton;
    MouseButton m_currentMouseButton;

public:
    RaylibApplication(RaylibWindowPtr window);

    static std::unique_ptr<RaylibApplication> create(RaylibWindowPtr window);

    void setWindow(RaylibWindowPtr window);
    void setConfigFlags(unsigned int flags);
    void setTargetFPS(int fps);

    void loop();

    bool anyMouseButtonDown() const;
    bool noMouseButtonDown() const;

    MouseButton currentMouseButton() const;
    MouseButton lastMouseButton() const;
};

typedef std::unique_ptr<RaylibApplication> RaylibApplicationPtr;

} // namespace gui
