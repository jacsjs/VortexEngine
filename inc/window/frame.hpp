#pragma once

#include "../glad/glad.h"
#include <GLFW/glfw3.h>

#include <assert.h>

namespace vortexWindow
{
    class Frame
    {
        GLFWwindow* pGLWindow;
        
        const int WIDTH, HEIGHT;
        
        const char * title;
        
    public:
        Frame(const int width, const int height, const char* title);
        
        /**
         * Close this window and delete all pointers.
         */
        void close();
        
        
        /**
         * Return true when this window is still open. (Usage: engine loop)
         */
        inline bool isOpen() { return !glfwWindowShouldClose(pGLWindow); }
    
        /**
         * Return a pointer to the OpenGL window instance for this window.
         */
        inline GLFWwindow * getGLFWwindowInstance() { return pGLWindow; }
        
        inline const int getWidth() const { return WIDTH; }
        inline const int getHeight() const { return HEIGHT; }
    };
    
};
