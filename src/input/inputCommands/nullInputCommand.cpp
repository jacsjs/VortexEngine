#include "input/inputCommands/nullInputCommand.hpp"

#include <iostream> //TODO: Just for tesing, will not be needed later

vortexInput::NullInputCommand::NullInputCommand()
{
    
}

vortexInput::NullInputCommand::~NullInputCommand()
{
}

void vortexInput::NullInputCommand::release()
{
    std::cout << "NullCommand Release" << std::endl;
}

void vortexInput::NullInputCommand::press()
{
    std::cout << "NullCommand Press" << std::endl; 
}

void vortexInput::NullInputCommand::repeate()
{
    std::cout << "NullCommand Repeate" << std::endl; 
}
