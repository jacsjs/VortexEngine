#pragma once

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

namespace vortexMemory
{
    class DoubleEndedStackAllocator
    {
    private:
        
        uintptr_t begin_ptr;
        uintptr_t end_ptr;
        
    public:
        
        /**
         * Allocate memory and treat it as a double-ended stack.
         * 
         * @param alignment Desired alignment for this double-ended memory stack (recommended either 16 or 32)
         * 
         * @param size_bytes Total size of the entire double-ended memory stack.
         */
        DoubleEndedStackAllocator(int alignment, int size_bytes);
        
        ~DoubleEndedStackAllocator();
        
    };
};
