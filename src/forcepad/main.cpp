#include <raylib.h>

#include "gui/raylib_application.h"
#include "forcepad_window.h"

int main(void)
{
    auto window = forcepad::ForcePadWindow::create(1280, 1024, "ForcePad Window");

    auto app = gui::RaylibApplication::create(window);
    app->setConfigFlags(FLAG_MSAA_4X_HINT);
    app->setTargetFPS(60);
    app->loop();

    return 0;
}
