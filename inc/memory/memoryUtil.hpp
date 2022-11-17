#pragma once

#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline")
#pragma GCC target("avx2", "fma")

#include <stdlib.h>
#include <assert.h>
#include <cstdint>

#include <immintrin.h> //For accelerated memcopy

namespace vortexMemory
{
    
    /**
     * Allocate aligned memory in powers of 2.
     * 
     * Must be deallocated with @see freeAligned()
     * 
     * @param alignment
     * 
     * @param num_bytes
     */
    void* mallocAligned(size_t alignment, size_t num_bytes);
    
    /**
     * Free aligned memory, should only give pointers to memory allocated by
     * @see void* mallocAlligned()
     */
    void freeAligned(void * mem_ptr);
    
    /**
     * Cpy the requested amount to dest, from src
     * Requires that the memory be aligned to 16.
     * 
     * memcpyAlign32() to be desired ecause it copies faster.
     * 
     * @param src Address of data to copy.
     * 
     * @param dest Address of expected resulting location.
     * 
     * @param size_bytes Amount of bytes to copy.
     */
    void memcpyAlign16(void* src, void* dest, int size_bytes);
    
    /**
     * Cpy the requested amount to dest, from src
     * Requires that the memory be aligned to 32.
     * 
     * Use memcpyAlign16() only if data is not aligned to 32 or more,
     * as it copies slower.
     * 
     * @param src Address of data to copy.
     * 
     * @param dest Address of expected resulting location.
     * 
     * @param size_bytes Amount of bytes to copy.
     */
    void memcpyAlign32(void* src, void* dest, int size_bytes);
    
    /**
     * Clear a memory block aligned to 16.
     * This will set all data from the given address to size_bytes to 0.
     */
    void memclearAlign16(void* mem_ptr, int size_bytes);
    
    /**
     * Clear a memory block aligned to 32.
     * This will set all data from the given address to size_bytes to 0.
     */
    void memclearAlign32(void* mem_ptr, int size_bytes);
    
};
