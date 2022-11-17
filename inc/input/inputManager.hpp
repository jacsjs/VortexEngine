#pragma once

#include "../window/windowManager.hpp"
#include "../graphics/core/renderManager.hpp"
#include "inputMapping/abstractInputMapping.hpp"
#include "inputCommandFactory/inputCommandFactory.hpp"

namespace vortexInput
{
    class InputManager
    {
    private:
        AbstractInputMapping * currentMapping;
        
        vortexGraphics::RenderManager * renderManager;
        
        float m_lastXpos;
        float m_lastYpos;
        
        float m_mouseSensitivity;
        
    public:
        
        InputManager();
        
        ~InputManager();
        
        /**
         * @return InputManager Singleton instance of this class.
         */
        static InputManager & instance();
        
        void setCurrentInputMapping(AbstractInputMapping * mapping);
        
        /**
         * Key event callback function for the active frame. (Is bound in @see frame.h)
         */
        void frame_key_callback(int key, int scancode, int action, int mode);
        
        /**
         * Mouse button event callback function for the active frame. (Is bound in @see frame.h)
         */
        void frame_mouse_button_callback(int button, int action, int mods);
        
        /**
         * Mouse scroll-wheel event callback function for the active frame. (Is bound in @see frame.h)
         */
        void frame_mouse_scroll_callback(double xOffset, double yOffset);
        
        /**
         * Mouse movement event callback function for the active frame. (Is bound in @see frame.h)
         */
        void frame_cursor_pos_callback(double xPos, double yPos);
        
    };
    
};
