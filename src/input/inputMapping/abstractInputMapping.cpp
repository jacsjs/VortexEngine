#include "input/inputMapping/abstractInputMapping.hpp"


vortexInput::AbstractInputMapping::AbstractInputMapping(vortexInput::InputCommandFactory* inputCommandFactory)
{
    this->inputCommandFactory = inputCommandFactory;
    for (int i = 0; i < inputArraySize; i++)
    {
        m_inputCommands[i] = inputCommandFactory->createInputCommand(InputCommandFactory::COMMAND_NULL);
    }
}

vortexInput::AbstractInputMapping::~AbstractInputMapping()
{
    for (int i = 0; i < inputArraySize; i++)
    {
        delete m_inputCommands[i];
    }
    
    delete this->inputCommandFactory;
}

void vortexInput::AbstractInputMapping::resetInputCommand(INPUT_COMMAND_INTERFACE interface, int button)
{
    this->assignInputCommand(interface, button, InputCommandFactory::COMMAND_NULL);
}

void vortexInput::AbstractInputMapping::invokeInputCommand(vortexInput::INPUT_COMMAND_INTERFACE interface, int button, int action)
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

void vortexInput::AbstractInputMapping::assignInputCommand(vortexInput::INPUT_COMMAND_INTERFACE interface, int button, InputCommandFactory::COMMAND_TO_CREATE command)
{
    if ((button + interface) > inputArraySize) return;
    
    delete m_inputCommands[interface + button]; //Delete old instance
    
    m_inputCommands[interface + button] = inputCommandFactory->createInputCommand(command); //create new instance.
}
