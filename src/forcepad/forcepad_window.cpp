#include "forcepad_window.h"

using namespace forcepad;
using namespace graphics;

#include "imgui.h"
#include "rlimgui/rlImGui.h"

static bool g_open = true;

ForcePadWindow::ForcePadWindow(int width, int height, std::string title)
    : RaylibWindow(width, height, title), m_renderTexture(nullptr), m_showMessageBox(false),
      m_appMode(AppMode::Material), m_drawingMode(DrawingMode::Brush), m_physicsMode(PhysicsMode::Load),
      m_brush(nullptr)
{
    m_brush = Brush::create(20.0, 255);
}

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

    if (currentMouseButton() == gui::MouseButton::LEFT_BUTTON)
        m_brush->apply(mouseX(), this->monitorHeight() - mouseY());

    m_renderTexture->endDraw();

    m_renderTexture->setScale(1.0);
    m_renderTexture->draw();

    DrawFPS(10, 40);
}

void ForcePadWindow::onDrawGui()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Start page", ""))
            {}

            ImGui::Separator();

            if (ImGui::MenuItem("New", "CTRL+N"))
            {}

            if (ImGui::MenuItem("Open", "CTRL+O"))
            {}

            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {}

            if (ImGui::MenuItem("Save as", "Ctrl+Shift+S"))
            {}

            ImGui::Separator();

            if (ImGui::MenuItem("Save as CALFEM...", ""))
            {}

            if (ImGui::MenuItem("Open from CALFEM...", ""))
            {}

            ImGui::Separator();

            if (ImGui::MenuItem("Preferences...", ""))
            {
                // m_settingsWindow->show();
                // m_settingsWindow->center();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Quit", "Alt+F4"))
            {
                // quitApplication = true;
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl-Z"))
            {}

            if (ImGui::MenuItem("Redo", "Ctrl-Y"))
            {}

            ImGui::Separator();

            if (ImGui::MenuItem("Copy", "Ctrl-C"))
            {}
            if (ImGui::MenuItem("Paste", "Ctlr-V"))
            {}

            ImGui::Separator();

            if (ImGui::MenuItem("Select all", "Ctrl-A"))
            {}
            if (ImGui::MenuItem("Select all nodes", ""))
            {}
            if (ImGui::MenuItem("Select all elements", ""))
            {}

            ImGui::Separator();

            if (ImGui::MenuItem("Fix selected nodes", ""))
            {}
            if (ImGui::MenuItem("Fix position selected nodes", ""))
            {}

            ImGui::Separator();

            if (ImGui::MenuItem("Fix ground nodes", ""))
            {}
            if (ImGui::MenuItem("Fix position ground nodes", ""))
            {}

            ImGui::Separator();

            if (ImGui::MenuItem("Subdivide element", "Ctrl-D"))
            {}

            ImGui::Separator();

            if (ImGui::MenuItem("Mesh selected", "Ctrl-M"))
            {}
            if (ImGui::MenuItem("Surface selected no ground", ""))
            {}
            if (ImGui::MenuItem("Surface selected with ground", ""))
            {}

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Properties...", ""))
            {}

            ImGui::Separator();

            if (ImGui::MenuItem("Node loads...", ""))
            {}

            if (ImGui::MenuItem("Element loads...", ""))
            {}

            if (ImGui::MenuItem("Materials...", ""))
            {}

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Mode"))
        {
            if (ImGui::MenuItem("Model", ""))
            {}
            if (ImGui::MenuItem("Geometry", ""))
            {}
            if (ImGui::MenuItem("Results", ""))
            {}
            if (ImGui::MenuItem("Feedback", ""))
            {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Results"))
        {
            if (ImGui::MenuItem("Normal", ""))
            {}
            if (ImGui::MenuItem("Torsion", ""))
            {}
            if (ImGui::MenuItem("Shear", ""))
            {}
            if (ImGui::MenuItem("Moment", ""))
            {}
            if (ImGui::MenuItem("Navier", ""))
            {}
            if (ImGui::MenuItem("No results", ""))
            {}

            ImGui::Separator();

            if (ImGui::MenuItem("X-ray mode", "Alt-X"))
            {}

            ImGui::Separator();

            if (ImGui::MenuItem("Scaling settings...", ""))
            {}

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About...", ""))
            {}
            if (ImGui::MenuItem("Homepage...", ""))
            {
#ifdef WIN32
                // ShellExecuteW(0, 0, L"https://jonaslindemann.github.io/objectiveframe/", 0, 0, SW_SHOW);
#endif
            }
            ImGui::Separator();

            if (ImGui::MenuItem("Log...", ""))
            {}

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // ImGui::ShowDemoWindow(&g_open);
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

void forcepad::ForcePadWindow::setAppMode(AppMode mode)
{
    m_appMode = mode;
}

AppMode forcepad::ForcePadWindow::appMode() const
{
    return m_appMode;
}

void forcepad::ForcePadWindow::setDrawingMode(DrawingMode mode)
{
    m_drawingMode = mode;
}

DrawingMode forcepad::ForcePadWindow::drawingMode() const
{
    return m_drawingMode;
}

void forcepad::ForcePadWindow::setPhysicsMode(PhysicsMode mode)
{
    m_physicsMode = mode;
}

PhysicsMode forcepad::ForcePadWindow::physicsMode() const
{
    return m_physicsMode;
}
