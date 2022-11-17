#include "input/inputCommandFactory/inputCommandFactory.hpp"

vortexInput::InputCommandFactory::InputCommandFactory()
{
}

vortexInput::InputCommandFactory::~InputCommandFactory()
{
    
}

vortexInput::AbstractInputCommand * vortexInput::InputCommandFactory::createInputCommand(vortexInput::InputCommandFactory::COMMAND_TO_CREATE command)
{
    AbstractInputCommand * retCommand = nullptr;
    switch( command )
    {
        case COMMAND_NULL:
            retCommand = new NullInputCommand{};
            break;
            
        case COMMAND_CAMERA_LEFT:
            retCommand = new CameraLeftCommand{};
            break;
            
        case COMMAND_CAMERA_RIGHT:
            retCommand = new CameraRightCommand{};
            break;

        case COMMAND_CAMERA_UP:
            retCommand = new CameraUpCommand{};
            break;
        
        case COMMAND_CAMERA_DOWN:
            retCommand = new CameraDownCommand{};
            break;
        
        case COMMAND_CAMERA_IN:
            retCommand = new CameraInCommand{};
            break;
        
        case COMMAND_CAMERA_OUT:
            retCommand = new CameraOutCommand{};
            break;
            
        default:
            retCommand = new NullInputCommand{};
            break;
    };
    return retCommand;
}

