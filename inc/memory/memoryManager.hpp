#pragma once

#include "allocator/poolAllocator.hpp"
namespace vortexMemory
{
    enum MEMORY_ELEMENT_TYPE
    {
        TYPE_VEC2 = 0,
        TYPE_VEC3 = 1,
        TYPE_VEC4 = 2,

        TYPE_MAT2 = 3,
        TYPE_MAT3 = 4,
        TYPE_MAT4 = 5
    };
    
    class MemoryManager
    {
    private:
            
        PoolAllocator ** pools; //Array of pointers to specilized pool allocators.
        
        
    public:
        
        MemoryManager();    
        
        ~MemoryManager();
        
        /**
         * @return InputManager Singleton instance of this class.
         */
        static MemoryManager & instance();
        
        void freePoolMem(MEMORY_ELEMENT_TYPE type, void* addr);
        
        void * requestPoolMem(MEMORY_ELEMENT_TYPE type);
        
        void * requestDynamicMem();
        
        void * requestTempMem();
        
        void * requestFrameMem();
        
        void * requestFrameBufferMem();
        
    };
};
