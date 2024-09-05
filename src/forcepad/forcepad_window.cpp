#include "forcepad_window.h"

#include <filesystem>
#include <iostream>

using namespace forcepad;
using namespace graphics;
using namespace gui;

#include <imgui.h>
#include <rlimgui/rlImGui.h>

static bool g_open = false;

ForcePadWindow::ForcePadWindow(int width, int height, std::string title)
    : RaylibWindow(width, height, title), m_renderTexture(nullptr), m_showMessageBox(false),
      m_appMode(AppMode::Material), m_drawingMode(DrawingMode::Brush), m_physicsMode(PhysicsMode::Load),
      m_brush(nullptr), m_eraser(nullptr), m_aboutWindow(nullptr), m_toolbarWindow(nullptr), m_progPath(""),
      m_imagePath(""), m_fontPath(""), m_progPathStr(""), m_currentColor(BLACK), m_colorPicker(nullptr),
      m_drawing(nullptr), m_layerWindow(nullptr), m_overlayTexture(nullptr), m_mouseX(-1.0f), m_mouseY(-1.0f),
      m_mouseDown(false), m_mouseDownX(-1), m_mouseDownY(-1), m_mouseUpX(-1), m_mouseUpY(-1), m_newRectangle(nullptr),
      m_newEllipse(nullptr), m_newLine(nullptr)
{}

void ForcePadWindow::onSetup()
{
    namespace fs = std::filesystem;

    SetTargetFPS(60);

    m_brush = Brush::create(20.0, 255);
    m_brush->setColor(BLACK);
    m_brush->setBlending(true);
    m_brush->setBlendMode(BLEND_ALPHA);

    m_eraser = Brush::create(20.0, 255);
    m_eraser->setColor(BLANK);
    m_eraser->setBlending(true);
    m_eraser->setBlendMode(BLEND_SUBTRACT_COLORS);

    m_renderTexture = RaylibRenderTexture::create();
    m_renderTexture->load(this->monitorWidth(), this->monitorHeight());

    m_overlayTexture = RaylibRenderTexture::create();
    m_overlayTexture->load(this->monitorWidth(), this->monitorHeight());

    m_drawing = Drawing::create(this->monitorWidth(), this->monitorHeight());
    m_drawing->addLayer();
    m_drawing->addLayer();

    m_aboutWindow = AboutWindow::create("About ForcePad");
    m_aboutWindow->setVisible(false);
    m_aboutWindow->setVersion("Version 3.0.0");
    m_aboutWindow->setRelease("Release Alfa");
    m_aboutWindow->setAuthor1("Jonas Lindemann");

    m_colorPicker = ColorPicker::create();
    m_colorPicker->setVisible(false);

    m_linePropWindow = LinePropWindow::create();
    m_linePropWindow->setVisible(false);

    m_layerWindow = LayerWindow::create();
    m_layerWindow->setVisible(false);
    m_layerWindow->setDrawing(m_drawing);

    m_toolbarWindow = ToolbarWindow::create("Drawing");

    m_toolbarWindow->setVisible(true);

    m_toolbarWindow->addButton("Select", ToolbarButtonType::RadioButton,
                               (m_imagePath / fs::path("tlselect.png")).string(), 1);
    m_toolbarWindow->addButton("Move", ToolbarButtonType::RadioButton, (m_imagePath / fs::path("tlmove.png")).string(),
                               1);
    m_toolbarWindow->addButton("Box select", ToolbarButtonType::RadioButton,
                               (m_imagePath / fs::path("square-dashed-solid.png")).string(), 1);
    m_toolbarWindow->addButton("Select color", ToolbarButtonType::Button,
                               (m_imagePath / fs::path("palette-solid.png")).string());
    m_toolbarWindow->addButton("Layers", ToolbarButtonType::Button,
                               (m_imagePath / fs::path("layer-group-solid.png")).string());
    m_toolbarWindow->addButton("Brush", ToolbarButtonType::RadioButton,
                               (m_imagePath / fs::path("paintbrush-fine-solid.png")).string(), 1);
    m_toolbarWindow->addButton("Eraser", ToolbarButtonType::RadioButton,
                               (m_imagePath / fs::path("eraser-solid.png")).string(), 1);
    m_toolbarWindow->addButton("Rectangle", ToolbarButtonType::RadioButton,
                               (m_imagePath / fs::path("square-solid.png")).string(), 1);
    m_toolbarWindow->addButton("Ellipse", ToolbarButtonType::RadioButton,
                               (m_imagePath / fs::path("circle-solid.png")).string(), 1);
    m_toolbarWindow->addButton("Line", ToolbarButtonType::RadioButton, (m_imagePath / fs::path("line.png")).string(),
                               1);

    m_toolbarWindow->setSize(200, 30);

    using std::placeholders::_1;
    m_toolbarWindow->assignOnButtonClicked(std::bind(&ForcePadWindow::onButtonClicked, this, std::placeholders::_1));
    m_toolbarWindow->assignOnButtonHover(std::bind(&ForcePadWindow::onButtonHover, this, std::placeholders::_1));
    m_colorPicker->assignOnColorChanged(std::bind(&ForcePadWindow::onColorChanged, this, std::placeholders::_1));
    m_colorPicker->setColor(m_currentColor);

    // m_toolbarWindow->addSpacer();
    // m_toolbarWindow->addButton("Inspect", OfToolbarButtonType::Button,
    //                            (m_imagePath / fs::path("tlinspect.png")).string());
    // m_toolbarWindow->addButton("Delete", OfToolbarButtonType::Button,
    //                            (m_imagePath / fs::path("tldelete.png")).string());
    // m_toolbarWindow->addSpacer();
    // m_toolbarWindow->addButton("Feedback", OfToolbarButtonType::RadioButton,
    //                            (m_imagePath / fs::path("tlfeedback.png")).string(), 1);
    // m_toolbarWindow->addButton("Run", OfToolbarButtonType::Button, (m_imagePath / fs::path("run.png")).string());
}

void ForcePadWindow::onButtonClicked(gui::ToolbarButton &button)
{
    std::cout << "onButtonClicked: " + button.name() << "\n";
    if (button.name() == "Box select")
        setDrawingMode(DrawingMode::SelectRect);
    else if (button.name() == "Brush")
        setDrawingMode(DrawingMode::Brush);
    else if (button.name() == "Eraser")
        setDrawingMode(DrawingMode::Eraser);
    else if (button.name() == "Select")
        setDrawingMode(DrawingMode::SelectShape);
    else if (button.name() == "Move")
        setDrawingMode(DrawingMode::Move);
    else if (button.name() == "Rectangle")
        setDrawingMode(DrawingMode::Rectangle);
    else if (button.name() == "Ellipse")
        setDrawingMode(DrawingMode::Ellipse);
    else if (button.name() == "Line")
    {
        setDrawingMode(DrawingMode::Line);
        m_linePropWindow->setStrokeWidth(5.0f);
        m_linePropWindow->show();
    }

    if (button.name() == "Select color")
    {
        m_colorPicker->setVisible(true);

        m_linePropWindow->setVisible(true);
    }

    if (button.name() == "Layers")
    {
        m_layerWindow->setVisible(true);
    }
}

void ForcePadWindow::onButtonHover(gui::ToolbarButton &button)
{}

void forcepad::ForcePadWindow::onColorChanged(Color color)
{
    m_currentColor = color;
    m_brush->setColor(color);
}

void ForcePadWindow::onDraw()
{
    ClearBackground(WHITE);

    m_drawing->beginDraw();

    if (currentMouseButton() == gui::MouseButton::LEFT_BUTTON)
    {
        if (m_drawingMode == DrawingMode::Brush)
            m_brush->apply(mouseX(), this->monitorHeight() - mouseY());
        else if (m_drawingMode == DrawingMode::Eraser)
            m_eraser->apply(mouseX(), this->monitorHeight() - mouseY());
    }

    m_drawing->endDraw();

    m_drawing->updateMouse(mouseX(), mouseY());
    m_drawing->draw();

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
            {
                m_aboutWindow->setVisible(true);
            }
            if (ImGui::MenuItem("Homepage...", ""))
            {
#ifdef WIN32
                // ShellExecuteW(0, 0, L"https://jonaslindemann.github.io/objectiveframe/", 0, 0, SW_SHOW);
#endif
            }
            ImGui::Separator();

            if (ImGui::MenuItem("Log...", ""))
            {}

            if (ImGui::MenuItem("Demo window", ""))
            {
                g_open = !g_open;
            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (g_open)
        ImGui::ShowDemoWindow(&g_open);

    m_aboutWindow->draw();
    m_toolbarWindow->draw();
    m_colorPicker->draw();
    m_layerWindow->draw();
    m_linePropWindow->draw();
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
    std::printf("mouse down at %f, %f\n", x, y);

    m_mouseDown = true;
    m_mouseDownX = x;
    m_mouseDownY = y;

    if (m_drawingMode == DrawingMode::Rectangle)
    {
        m_newRectangle = graphics::Rectangle::create();
        m_newRectangle->setFillColor(m_currentColor);
        m_newRectangle->setStrokeColor(m_linePropWindow->strokeColor());
        m_newRectangle->setStrokeWidth(m_linePropWindow->strokeWidth());
        m_newRectangle->setP0(Vector2{x, y});
        m_newRectangle->setP1(Vector2{x, y});
        m_drawing->setNewShape(m_newRectangle);
    }

    if (m_drawingMode == DrawingMode::Ellipse)
    {
        m_newEllipse = graphics::Ellipse::create();
        m_newEllipse->setFillColor(m_currentColor);
        m_newEllipse->setStrokeColor(m_linePropWindow->strokeColor());
        m_newEllipse->setStrokeWidth(m_linePropWindow->strokeWidth());
        m_newEllipse->setP0(Vector2{x, y});
        m_newEllipse->setRadiusX(0.0f);
        m_newEllipse->setRadiusY(0.0f);
        m_drawing->setNewShape(m_newEllipse);
    }

    if (m_drawingMode == DrawingMode::Line)
    {
        m_newLine = graphics::Line::create();
        m_newLine->setStrokeColor(m_linePropWindow->strokeColor());
        m_newLine->setStrokeWidth(m_linePropWindow->strokeWidth());
        m_newLine->setP0(Vector2{x, y});
        m_newLine->setP1(Vector2{x, y});
        m_drawing->setNewShape(m_newLine);
    }
    /*
    else if (m_drawingMode == DrawingMode::SelectRect)
    {
        m_drawing->beginSelectRect(x, y);
    }
    else if (m_drawingMode == DrawingMode::SelectShape)
    {
        m_drawing->beginSelectShape(x, y);
    }
    else if (m_drawingMode == DrawingMode::Move)
    {
        m_drawing->beginMove(x, y);
    }
    */
}

void ForcePadWindow::onMouseMove(float x, float y)
{
    std::printf("mouse moved to %f, %f\n", x, y);
    m_mouseX = x;
    m_mouseY = y;

    if (m_drawingMode == DrawingMode::Rectangle)
    {
        if (m_newRectangle != nullptr)
            m_newRectangle->setP1(Vector2{x, y});
    }

    if (m_drawingMode == DrawingMode::Ellipse)
    {
        if (m_newEllipse != nullptr)
        {
            auto dx = x - m_newEllipse->p0().x;
            auto dy = y - m_newEllipse->p0().y;

            std::printf("dx: %f, dy: %f\n", dx, dy);
            m_newEllipse->setRadiusX(dx);
            m_newEllipse->setRadiusY(dy);
        }
    }

    if (m_drawingMode == DrawingMode::Line)
    {
        if (m_newLine != nullptr)
            m_newLine->setP1(Vector2{x, y});
    }
}

void forcepad::ForcePadWindow::onMouseReleased(gui::MouseButton button, float x, float y)
{
    std::printf("mouse released at %f, %f\n", x, y);
    m_mouseDown = false;
    m_mouseUpX = x;
    m_mouseUpY = y;

    if (m_drawingMode == DrawingMode::Rectangle)
    {
        if (m_newRectangle != nullptr)
        {
            m_newRectangle->setP1(Vector2{x, y});
            m_drawing->currentLayer()->addShape(m_newRectangle);
            m_drawing->clearNewShape();
            m_newRectangle = nullptr;
        }
    }

    if (m_drawingMode == DrawingMode::Ellipse)
    {
        if (m_newEllipse != nullptr)
        {
            m_drawing->currentLayer()->addShape(m_newEllipse);
            m_drawing->clearNewShape();
            m_newEllipse = nullptr;
        }
    }

    if (m_drawingMode == DrawingMode::Line)
    {
        if (m_newLine != nullptr)
        {
            m_drawing->currentLayer()->addShape(m_newLine);
            m_drawing->clearNewShape();
            m_newLine = nullptr;
        }
    }
}

void ForcePadWindow::onKeyPressed(int key)
{
    std::printf("key pressed: %d\n", key);
}

std::shared_ptr<ForcePadWindow> ForcePadWindow::create(int width, int height, std::string title)
{
    return std::make_shared<ForcePadWindow>(width, height, title);
}

void forcepad::ForcePadWindow::setProgPath(std::string path)
{
    m_progPathStr = path;

    namespace fs = std::filesystem;

    m_progPath.assign(m_progPathStr);

    m_fontPath = m_progPath / fs::path("fonts");
    m_imagePath = m_progPath / fs::path("images");
    // m_pluginPath = m_progPath / fs::path("plugins");
    // m_mapPath = m_progPath / fs::path("maps");
    // m_pythonPath = m_progPath / fs::path("python");
    // m_examplePath = m_progPath / fs::path("examples");
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

    if (mode == DrawingMode::Brush)
    {
        m_brush->setColor(m_currentColor);
    }
    else if (mode == DrawingMode::Eraser)
    {
        m_brush->setColor(BLANK);
    }
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
