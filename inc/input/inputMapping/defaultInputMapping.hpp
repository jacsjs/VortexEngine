#pragma once

#include "abstractInputMapping.hpp"
namespace vortexInput
{
    class DefaultInputMapping : public AbstractInputMapping
    {
        
    public:
        
        DefaultInputMapping(InputCommandFactory * inputCommandFactory);
        
        virtual ~DefaultInputMapping();
        
        void invokeInputCommand(vortexInput::INPUT_COMMAND_INTERFACE interface, int button, int action) override;
        
        void assignInputCommand(vortexInput::INPUT_COMMAND_INTERFACE interface, int button, InputCommandFactory::COMMAND_TO_CREATE command) override;
    };
};
