#include <gui/about_window.h>

#include <imgui.h>

using namespace gui;

AboutWindow::AboutWindow(const std::string name) : UiWindow(name)
{}

AboutWindow::~AboutWindow()
{}

std::shared_ptr<AboutWindow> AboutWindow::create(const std::string name)
{
    return std::make_shared<AboutWindow>(name);
}

void gui::AboutWindow::setVersion(std::string text)
{
    m_versionString = text;
}

void gui::AboutWindow::setRelease(std::string text)
{
    m_release = text;
}

void gui::AboutWindow::setCopyright(std::string text)
{
    m_copyright = text;
}

void gui::AboutWindow::setAuthor1(std::string text)
{
    m_author1 = text;
}

void gui::AboutWindow::setAuthor2(std::string text)
{
    m_author2 = text;
}

void gui::AboutWindow::setExtra1(std::string text)
{
    m_extra1 = text;
}

void AboutWindow::doDraw()
{
    ImGui::Dummy(ImVec2(400.0, 0.0));
    ImGui::Text(m_versionString.c_str());
    ImGui::Separator();
    ImGui::Text(m_release.c_str());
    ImGui::Text(m_copyright.c_str());
    ImGui::Separator();
    ImGui::Text(m_author1.c_str());
    ImGui::Text(m_author2.c_str());
    ImGui::Separator();
    ImGui::Text(m_extra1.c_str());
}
