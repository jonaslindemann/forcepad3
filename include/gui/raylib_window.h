#pragma once

#include "raylib.h"
#include <string>
#include <memory>

namespace gui {

enum class MouseButton {
    LEFT_BUTTON,
    RIGHT_BUTTON,
    MIDDLE_BUTTON,
    NO_BUTTON
};

class RaylibApplication;

class RaylibWindow {
private:
    int m_width{1024};
    int m_height{768};
    std::string m_title{"Raylib window"};

    RaylibApplication *m_app{nullptr};

public:
    RaylibWindow(int width, int height, std::string title);

    static std::shared_ptr<RaylibWindow> create(int width, int height, std::string title);

    void setApplication(RaylibApplication *app);
    RaylibApplication *application() const;

    void setState(unsigned int flags);

    void setWidth(int width);
    void setHeight(int height);
    int width() const;
    int height() const;
    float widthF() const;
    float heightF() const;
    std::string title() const;

    int screenWidth() const;
    int screenHeight() const;
    int monitorWidth() const;
    int monitorHeight() const;

    float mouseX() const;
    float mouseY() const;

    MouseButton currentMouseButton() const;

    virtual void onInit();
    virtual void onSetup();
    virtual void onClear();
    virtual void onUpdate();
    virtual void onDraw();
    virtual void onDrawGui();
    virtual void onResize(int width, int height);
    virtual void onKeyPressed(int key);
    virtual void onMousePressed(MouseButton button, float x, float y);
    virtual void onMouseDown(MouseButton button, float x, float y);
    virtual void onMouseMove(float x, float y);
    virtual void onMouseReleased(MouseButton button, float x, float y);
    virtual void onClose();
};

typedef std::shared_ptr<RaylibWindow> RaylibWindowPtr;

} // namespace gui
