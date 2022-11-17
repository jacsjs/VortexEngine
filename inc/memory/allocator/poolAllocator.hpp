#pragma once

#include "../memoryUtil.hpp" //Aligned allocator and other utility

#include <assert.h> //For assert, ensuring safe operations
#include <stdint.h> //For unsigned int conversion of pointers

namespace vortexMemory
{
    class PoolAllocator
    {
    private:

        uintptr_t first_chunk;
        uintptr_t last_chunk;
        
        uintptr_t begin_ptr;
        
        int poolAlignment;
        int chunkSize_bytes;
        int num_chunks;
        
    public:
        
        /**
         * Allocate memory in blocks of n bytes with x amount of blocks.
         * 
         * @param alignment Desired alignment for this memory pool (recommended either 16 or 32)
         * 
         * @param num_chunks Number of reserved memory chunks. (I.e. Maximum number of chunks.)
         * 
         * @param poolSize_bytes Size per memory blocks.
         */
        PoolAllocator(int alignment, int num_chunks, int chunkSize_bytes);
        
        ~PoolAllocator();
        
        /**
         * Get a pointer to the next free memory chunk
         * 
         * @throws Assert error if not enough space,
         *          thus recommended to call @see hasFreeChunk()
         *          before.
         * 
         * @return void* Free memory block
         */
        void * allocChunk();
        
        /**
         * Free the requested memory chunk.
         */
        void freeChunk(void * chunk_ptr);
        
        /**
         * Deallocate all memory in this pool and reset its structure.
         */
        void clear();
        
        /**
         * Checks if the given pointer belong to a chunk allocated by this poolAllocator.
         * 
         * This check is automatically called when trying to free a chunk 
         * @see freeChunk(void * chunk_ptr)
         */
        bool resideInPool(void * mem_ptr);
        
        /**
         * @return int How many empty chunks are left in this pool.
         */
        int spaceRemaining();
        
        /**
         * @return bool True if atleast one memory block is free.
         */
        inline bool hasFreeChunk() { return true; }
        
        /**
         * @return int Capacity for this pool allocator, 
         *             expressed in number of allocatable chunks.
         */
        inline int capacity() { return num_chunks; }
        
        /**
         * @return int Size per chunk in bytes.
         */
        inline int chunkSize() { return chunkSize_bytes; }
        
        /**
         * @return int Memory lignment for this pool.
         */
        inline int alignment() { return poolAlignment; }
        
        /**
         * @return void* Pointer to first address of this pool allocator.
         */
        inline void * firstAddress() { return reinterpret_cast<void*>(first_chunk); }

        /**
         * @return int The minumim size of a chunk expressed in bytes.
         * 
         * This is architecture specific.
         */
        static int minChunkSize();
    };
};
