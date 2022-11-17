#pragma once

//This is the file where all commands are included, NOTE: Only include this header when working with commands
#include "../inputCommands/abstractInputCommand.hpp"
#include "../inputCommands/nullInputCommand.hpp"


#include "../inputCommands/cameraCommands/cameraLeftCommand.hpp"
#include "../inputCommands/cameraCommands/cameraRightCommand.hpp"
#include "../inputCommands/cameraCommands/cameraUpCommand.hpp"
#include "../inputCommands/cameraCommands/cameraDownCommand.hpp"
#include "../inputCommands/cameraCommands/cameraInCommand.hpp"
#include "../inputCommands/cameraCommands/cameraOutCommand.hpp"

#include "../../graphics/core/renderManager.hpp"
#include "../../window/windowManager.hpp"

namespace vortexInput
{
    class InputCommandFactory
    {
        
    private:
        
    public:

        enum COMMAND_TO_CREATE
        {
            COMMAND_NULL,
            COMMAND_CAMERA_LEFT,
            COMMAND_CAMERA_RIGHT,
            COMMAND_CAMERA_UP,
            COMMAND_CAMERA_DOWN,
            COMMAND_CAMERA_IN,
            COMMAND_CAMERA_OUT
        };
        
        
        InputCommandFactory();
        ~InputCommandFactory();
        
        /**
         * @return AbstractInputCommand Command created with new
         * 
         * NOTE: Must explicitly be deleted with delete.
         * 
         * Returns a nullCommand if the command was not found.
         * 
         */
        AbstractInputCommand * createInputCommand(COMMAND_TO_CREATE command);
        
    };
};
