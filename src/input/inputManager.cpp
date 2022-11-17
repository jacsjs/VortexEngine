#include "input/inputManager.hpp"

vortexInput::InputManager::InputManager()
{
    using namespace vortexWindow;
    using namespace vortexGraphics;
    
    renderManager = &RenderManager::instance();
    
    //For testing purposes only 
    m_lastXpos = WindowManager::instance().getFrame()->getWidth() / 2;
    m_lastYpos = WindowManager::instance().getFrame()->getHeight() / 2;
    
    m_mouseSensitivity = 0.5f;
    
    auto glfwWindow = WindowManager::instance().getFrame()->getGLFWwindowInstance();
    
    glfwSetWindowUserPointer(glfwWindow, this);

    glfwSetKeyCallback(glfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mode) 
    { 
        //Static cast because glfwGetWindowUserPointer returns of type void*, but we know it is of type inputManager
        static_cast<vortexInput::InputManager*>(glfwGetWindowUserPointer(window))->frame_key_callback(key, scancode, action, mode);  
    });
    
    glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* window, int button, int action, int mods) 
    { 
        static_cast<vortexInput::InputManager*>(glfwGetWindowUserPointer(window))->frame_mouse_button_callback(button, action , mods);  
    });
    
    glfwSetScrollCallback(glfwWindow, [](GLFWwindow* window, double xOffset, double yOffset) 
    { 
        static_cast<vortexInput::InputManager*>(glfwGetWindowUserPointer(window))->frame_mouse_scroll_callback(xOffset, yOffset);  
    });
    
    glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow* window, double xPos, double yPos) 
    { 
        static_cast<vortexInput::InputManager*>(glfwGetWindowUserPointer(window))->frame_cursor_pos_callback(xPos, yPos);  
    });
}

vortexInput::InputManager & vortexInput::InputManager::instance()
{
    static vortexInput::InputManager singleton{};
    return singleton; 
}

vortexInput::InputManager::~InputManager()
{
    delete currentMapping;
}

void vortexInput::InputManager::setCurrentInputMapping(vortexInput::AbstractInputMapping* mapping)
{
    currentMapping = mapping;
}


void vortexInput::InputManager::frame_key_callback(int key, int scancode, int action, int mode)
{
    currentMapping->invokeInputCommand(INPUT_INTERFACE_KEY, key, action);
}

void vortexInput::InputManager::frame_mouse_button_callback(int button, int action, int mods)
{
    currentMapping->invokeInputCommand(INPUT_INTERFACE_MOUSE_BUTTON, button, action);
}

void vortexInput::InputManager::frame_mouse_scroll_callback(double xOffset, double yOffset)
{
}

void vortexInput::InputManager::frame_cursor_pos_callback(double xPos, double yPos)
{
    vortexMath::Vec3<float> temp{ static_cast<float>( m_lastYpos - yPos ), static_cast<float>( m_lastXpos - xPos ), 0.0f };
    temp.normalize();
    temp *= m_mouseSensitivity;
    renderManager->getCurrentScene()->activeCamera()->updateOrientation(temp);
    m_lastXpos = xPos;
    m_lastYpos = yPos;
}
