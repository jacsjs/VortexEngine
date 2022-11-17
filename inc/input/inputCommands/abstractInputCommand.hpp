#pragma once

namespace vortexInput
{
    class AbstractInputCommand
    {
    public:
            
        AbstractInputCommand();
        virtual ~AbstractInputCommand();
        
        /**
         * Release button action.
         */
        virtual void release() = 0;
        
        /**
         * Press button action.
         */
        virtual void press() = 0;
        
        /**
         * Hold button action.
         */
        virtual void repeate() = 0;
        
    };
};
