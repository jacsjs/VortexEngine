#pragma once

#include "../../graphics/core/renderManager.hpp"
#include "../inputCommandFactory/inputCommandFactory.hpp"
   
#include <GLFW/glfw3.h>

namespace vortexInput
{
    enum INPUT_COMMAND_INTERFACE
    {
        INPUT_INTERFACE_KEY = 0,
        INPUT_INTERFACE_MOUSE_BUTTON = GLFW_KEY_LAST,
        INPUT_INTERFACE_JOYSTICK = GLFW_JOYSTICK_LAST
    };
    
    class AbstractInputMapping
    {
    protected:

        int inputArraySize = GLFW_KEY_LAST + GLFW_JOYSTICK_LAST + 8 + 4; //8 mouse buttons and 4 scroll actions.
        
        AbstractInputCommand* m_inputCommands[GLFW_KEY_LAST + GLFW_JOYSTICK_LAST + 8 + 4];
        
        InputCommandFactory * inputCommandFactory;
        
    public:
        
        AbstractInputMapping(InputCommandFactory * inputCommandFactory);
        
        virtual ~AbstractInputMapping();
        
        /**
         * Invoke the command currently bound to the given button.
         * 
         * Where action corresponds to the command's release(), press() and repeat() respectively.
         */
        virtual void invokeInputCommand(INPUT_COMMAND_INTERFACE interface, int button, int action) = 0;
        
        /**
         * Bind the given button of the given type to a new command. 
         */
        virtual void assignInputCommand(INPUT_COMMAND_INTERFACE interface, int button, InputCommandFactory::COMMAND_TO_CREATE command) = 0;
        
        /**
         * Bind the given button of the given type to nullInputCommand().
         */
        virtual void resetInputCommand(INPUT_COMMAND_INTERFACE interface, int button);
    };
    
};
