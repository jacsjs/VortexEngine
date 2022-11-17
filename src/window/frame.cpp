#include "window/frame.hpp"

vortexWindow::Frame::Frame(const int width, const int height, const char * title)
: WIDTH(width), HEIGHT(height), title(title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    pGLWindow = glfwCreateWindow(WIDTH, HEIGHT, title, nullptr, nullptr);
    
    if (pGLWindow == NULL)
    {
        glfwTerminate();
    }
    
    glfwMakeContextCurrent(pGLWindow);
    
    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

    glViewport(0, 0, WIDTH, HEIGHT);
}

void vortexWindow::Frame::close()
{
    glfwTerminate();
}
