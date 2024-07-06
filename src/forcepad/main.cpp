#include <string>
#include <filesystem>

#include <raylib.h>

#include <gui/raylib_application.h>

#include "forcepad_window.h"

int main(int argc, char **argv)
{
    std::string fullExePathStr = argv[0];

    namespace fs = std::filesystem;

    fs::path fullExePath(fullExePathStr);
    fs::path progPath = fullExePath.parent_path();

    auto window = forcepad::ForcePadWindow::create(1280, 1024, "ForcePad Window");
    window->setProgPath(progPath.string());

    auto app = gui::RaylibApplication::create(window);
    app->setConfigFlags(FLAG_MSAA_4X_HINT);
    app->setTargetFPS(60);
    app->loop();

    return 0;
}
