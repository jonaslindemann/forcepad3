#include "forcepad_window.h"

using namespace forcepad;
using namespace graphics;

#include "imgui.h"
#include "rlimgui/rlImGui.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

static bool g_open = true;

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

    BeginBlendMode(BLEND_ADDITIVE);
    if (currentMouseButton() == gui::MouseButton::LEFT_BUTTON)
    {
        DrawCircle(mouseX(), this->monitorHeight() - mouseY(), 20, Color{0, 0, 0, 32});
    }
    EndBlendMode();

    m_renderTexture->endDraw();

    m_renderTexture->setScale(1.0);
    m_renderTexture->draw();

    DrawFPS(10, 10);
}

void ForcePadWindow::onDrawGui()
{
    ImGui::ShowDemoWindow(&g_open);
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
