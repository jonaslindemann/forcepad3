#include "gui/raylib_application.h"

#include "imgui.h"
#include "rlimgui/rlImGui.h"

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

    // Windows initialisation

    m_window->onInit();

    // Setup ImGui config

    rlImGuiSetup(true);

    ImGuiIO &io = ImGui::GetIO();
    auto font = io.Fonts->AddFontFromFileTTF("data/RopaSans-Regular.ttf", 18);
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
    io.FontDefault = font;

    m_window->onConfigGui();

    // Setup ImGui style

    ImGuiStyle &style = ImGui::GetStyle();
    ImGuiStyle newStyle;

    newStyle.FrameRounding = 4;
    newStyle.WindowRounding = 8;
    newStyle.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.5f);
    newStyle.Colors[ImGuiCol_TitleBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.8f);
    newStyle.Colors[ImGuiCol_TitleBgActive] =
        ImVec4(newStyle.Colors[ImGuiCol_TitleBgActive].x, newStyle.Colors[ImGuiCol_TitleBgActive].y,
               newStyle.Colors[ImGuiCol_TitleBgActive].z, 0.8f);

    newStyle.ScaleAllSizes(1.0f);
    io.FontGlobalScale = 1.0f;

    style = newStyle;

    m_window->onStyleGui();

    rlImGuiReloadFonts();

    // Call custom setup method

    m_window->onSetup();

    // Initialize state variables

    m_mousePos = GetMousePosition();
    m_lastMousePos = m_mousePos;

    // Main loop

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

        if (!ImGui::GetIO().WantCaptureMouse)
        {

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
        }
        else
        {
            m_currentMouseButton = MouseButton::NO_BUTTON;
            m_lastMouseButton = MouseButton::NO_BUTTON;
        }

        // Call custom update and draw methods

        m_window->onUpdate();
        m_window->onClear();

        // Start drawing

        BeginDrawing();

        // Call window draw method

        m_window->onDraw();

        // Draw ImGui

        rlImGuiBegin();

        // Set ImGui window flags

        ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;

        ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                        ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        // Handle docking

        ImGui::Begin("DockSpace", nullptr, window_flags);
        ImGui::PopStyleVar(3);

        ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_AutoHideTabBar;
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        ImGui::End();

        // Custom GUI drawing method

        m_window->onDrawGui();

        rlImGuiEnd();

        EndDrawing();
    }

    // Call window close method.

    m_window->onClose();

    // Close window

    CloseWindow();
}

bool gui::RaylibApplication::anyMouseButtonDown() const
{
    if (ImGui::GetIO().WantCaptureMouse)
        return false;

    return IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_RIGHT_BUTTON) ||
           IsMouseButtonDown(MOUSE_MIDDLE_BUTTON);
}

bool gui::RaylibApplication::noMouseButtonDown() const
{
    if (ImGui::GetIO().WantCaptureMouse)
        return true;

    return !IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !IsMouseButtonDown(MOUSE_RIGHT_BUTTON) &&
           !IsMouseButtonDown(MOUSE_MIDDLE_BUTTON);
}

gui::MouseButton gui::RaylibApplication::currentMouseButton() const
{
    if (ImGui::GetIO().WantCaptureMouse)
        return MouseButton::NO_BUTTON;

    return m_currentMouseButton;
}

gui::MouseButton gui::RaylibApplication::lastMouseButton() const
{
    return m_lastMouseButton;
}
