#pragma once

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

#include "../memoryUtil.hpp"

namespace vortexMemory
{
    class StackAllocator
    {
    public:
        typedef uintptr_t marker_t;
        
    private:
        
        void * rawptr;
        
        marker_t begin_ptr;
        
        int size_bytes;
        
    public:
        
        /**
         * Allocate memory and treat it as a stack.
         * 
         * @param alignment Desired alignment for this memory stack (recommended either 16 or 32)
         * 
         * @param size_bytes Total size of the entire memory stack.
         */
        StackAllocator(int alignment, int size_bytes);
        
        ~StackAllocator();
        
        /**
         * Request an allocation of size_bytes bytes, and push this
         * onto the memory stack.
         *
         * @param size_bytes The amount of desired bytes to allocate, 
         *                   must be less than or equal to the remaining space. 
         */
        void * alloc(int size_bytes);
        
        /**
         * @return marker_t Pointer to current top stack.
         */ 
        inline marker_t getMarker() { return begin_ptr; }
        
        /**
         * Free to the desired Marker, given by @see getMarker();
         */
        void freeToMarker(marker_t begin_ptr);
        
        /**
         * Clear all data in this stack and reset marker to first element.
         */
        void clear();
    };
};
