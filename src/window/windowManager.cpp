#include "window/windowManager.hpp"

vortexWindow::WindowManager::WindowManager()
{
}

void vortexWindow::WindowManager::setupFrame(int width, int height, const char* title)
{
    frame = new Frame{ width, height, title };
}

vortexWindow::WindowManager::~WindowManager()
{
    delete frame;
}

vortexWindow::WindowManager & vortexWindow::WindowManager::instance()
{
    static WindowManager singleton;
    return singleton;   
}

