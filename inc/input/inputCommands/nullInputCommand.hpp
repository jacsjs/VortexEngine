#pragma once

#include "abstractInputCommand.hpp"

#include <iostream>
namespace vortexInput
{
    class NullInputCommand : public AbstractInputCommand
    {
    public:
            
        NullInputCommand();
        ~NullInputCommand();
        virtual void release();
        virtual void press();
        virtual void repeate();
        
    };
};
