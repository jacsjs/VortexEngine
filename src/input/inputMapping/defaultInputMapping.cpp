#include "input/inputMapping/defaultInputMapping.hpp"

vortexInput::DefaultInputMapping::DefaultInputMapping(InputCommandFactory * inputCommandFactory)
: AbstractInputMapping(inputCommandFactory) //Same as super() in java
{
    assignInputCommand(INPUT_INTERFACE_KEY, GLFW_KEY_A, InputCommandFactory::COMMAND_CAMERA_LEFT);
    assignInputCommand(INPUT_INTERFACE_KEY, GLFW_KEY_D, InputCommandFactory::COMMAND_CAMERA_RIGHT);
    
    assignInputCommand(INPUT_INTERFACE_KEY, GLFW_KEY_W, InputCommandFactory::COMMAND_CAMERA_IN);
    assignInputCommand(INPUT_INTERFACE_KEY, GLFW_KEY_S, InputCommandFactory::COMMAND_CAMERA_OUT);
    
    assignInputCommand(INPUT_INTERFACE_KEY, GLFW_KEY_SPACE, InputCommandFactory::COMMAND_CAMERA_UP);
    
    assignInputCommand(INPUT_INTERFACE_KEY, GLFW_KEY_LEFT_SHIFT, InputCommandFactory::COMMAND_CAMERA_DOWN);
}

vortexInput::DefaultInputMapping::~DefaultInputMapping()
{
}

void vortexInput::DefaultInputMapping::invokeInputCommand(vortexInput::INPUT_COMMAND_INTERFACE interface, int button, int action)
{
    switch (action)
    {
        case 0:
            m_inputCommands[interface + button]->release();
            break;
        
        case 1:
            m_inputCommands[interface + button]->press();
            break;
            
        case 2:
            m_inputCommands[interface + button]->repeate();
            break;
            
        default:
            break;
    };
}

void vortexInput::DefaultInputMapping::assignInputCommand(vortexInput::INPUT_COMMAND_INTERFACE interface, int button, InputCommandFactory::COMMAND_TO_CREATE command)
{
    if ((button + interface) > inputArraySize) return;
    
    delete m_inputCommands[interface + button]; //Delete old instance
    
    m_inputCommands[interface + button] = inputCommandFactory->createInputCommand(command); //create new instance.
}


