#include <gui/console_window.h>

using namespace gui;

ConsoleWindow::ConsoleWindow(const std::string name) : UiWindow(name), m_autoScroll{false}
{
    // setWindowFlags(ImGuiWindowFlags_None);
    this->setWindowFlags(ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
                         ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
                         ImGuiWindowFlags_NoNav);

    clear();
}

std::shared_ptr<ConsoleWindow> gui::ConsoleWindow::create(const std::string name)
{
    return std::make_shared<ConsoleWindow>(name);
}

void gui::ConsoleWindow::clear()
{
    m_buffer.clear();
    m_lineOffsets.clear();
    m_lineOffsets.push_back(0);
}

void gui::ConsoleWindow::log(const std::string message)
{
    int old_size = m_buffer.size();
    m_buffer.append(message.c_str());
    for (int new_size = m_buffer.size(); old_size < new_size; old_size++)
        if (m_buffer[old_size] == '\n')
            m_lineOffsets.push_back(old_size + 1);
}

void gui::ConsoleWindow::doDraw()
{
    ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    const char *buf = m_buffer.begin();
    const char *buf_end = m_buffer.end();
    if (m_filter.IsActive())
    {
        for (int line_no = 0; line_no < m_lineOffsets.Size; line_no++)
        {
            const char *line_start = buf + m_lineOffsets[line_no];
            const char *line_end =
                (line_no + 1 < m_lineOffsets.Size) ? (buf + m_lineOffsets[line_no + 1] - 1) : buf_end;
            if (m_filter.PassFilter(line_start, line_end))
                ImGui::TextUnformatted(line_start, line_end);
        }
    }
    else
    {
        ImGuiListClipper clipper;
        clipper.Begin(m_lineOffsets.Size);
        while (clipper.Step())
        {
            for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
            {
                const char *line_start = buf + m_lineOffsets[line_no];
                const char *line_end =
                    (line_no + 1 < m_lineOffsets.Size) ? (buf + m_lineOffsets[line_no + 1] - 1) : buf_end;
                ImGui::TextUnformatted(line_start, line_end);
            }
        }
        clipper.End();
    }
    ImGui::PopStyleVar();

    // if (m_autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    //     ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();
}

void gui::ConsoleWindow::doPreDraw()
{
    this->setSize(700, 40);
    ImGui::SetNextWindowSize(ImVec2(700, 40), 0); // ImGuiCond_FirstUseEver);
}
