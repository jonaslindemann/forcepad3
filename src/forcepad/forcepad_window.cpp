#include "forcepad_window.h"

using namespace forcepad;
using namespace graphics;

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

ForcePadWindow::ForcePadWindow(int width, int height, std::string title)
    : RaylibWindow(width, height, title), m_renderTexture(nullptr), m_showMessageBox(false)
{}

void ForcePadWindow::onSetup()
{
    SetTargetFPS(60);

    m_renderTexture = RaylibRenderTexture::create();
    m_renderTexture->load(this->monitorWidth(), this->monitorHeight());
}

void ForcePadWindow::onDraw()
{
    ClearBackground(WHITE);
    m_renderTexture->beginDraw();

    BeginBlendMode(BLEND_ALPHA);
    if (currentMouseButton() == gui::MouseButton::LEFT_BUTTON)
    {
        DrawCircle(mouseX(), this->monitorHeight() - mouseY(), 20, Color{0, 0, 0, 64});
    }
    EndBlendMode();

    m_renderTexture->endDraw();

    m_renderTexture->draw(0, 0);

    // DrawText("ForcePAD", 20, 20, 20, WHITE);
    DrawFPS(10, 10);

    /*
    if (GuiButton(Rectangle{24, 24, 120, 30}, "#191#Show Message"))
        m_showMessageBox = true;

    if (m_showMessageBox)
    {
        int result =
            GuiMessageBox(Rectangle{85, 70, 250, 100}, "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

        if (result >= 0)
            m_showMessageBox = false;
    }
    */
}

void ForcePadWindow::onUpdate()
{}

void ForcePadWindow::onResize(int width, int height)
{
    std::printf("window resized to %d x %d\n", width, height);
}

void ForcePadWindow::onMousePressed(gui::MouseButton button, float x, float y)
{
    std::printf("mouse pressed at %f, %f\n", x, y);
}

void forcepad::ForcePadWindow::onMouseDown(gui::MouseButton button, float x, float y)
{
    // std::printf("mouse down at %f, %f\n", x, y);
}

void ForcePadWindow::onMouseMove(float x, float y)
{
    // std::printf("mouse moved to %f, %f\n", x, y);
}

void forcepad::ForcePadWindow::onMouseReleased(gui::MouseButton button, float x, float y)
{
    // std::printf("mouse released at %f, %f\n", x, y);
}

void ForcePadWindow::onKeyPressed(int key)
{
    std::printf("key pressed: %d\n", key);
}

std::shared_ptr<ForcePadWindow> ForcePadWindow::create(int width, int height, std::string title)
{
    return std::make_shared<ForcePadWindow>(width, height, title);
}
