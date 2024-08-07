#pragma once

#include <memory>
#include <string>
#include <vector>

#include <gui/ui_window.h>

namespace gui {

class AboutWindow : public UiWindow {
private:
    std::string m_versionString;
    std::string m_release;
    std::string m_copyright;
    std::string m_author1;
    std::string m_author2;
    std::string m_extra1;

public:
    AboutWindow(const std::string name);
    virtual ~AboutWindow();

    static std::shared_ptr<AboutWindow> create(const std::string name);

    void setVersion(std::string text);
    void setRelease(std::string text);
    void setCopyright(std::string text);
    void setAuthor1(std::string text);
    void setAuthor2(std::string text);
    void setExtra1(std::string text);

protected:
    virtual void doDraw();
};

typedef std::shared_ptr<AboutWindow> AboutWindowPtr;

} // namespace gui
