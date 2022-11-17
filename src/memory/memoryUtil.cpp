#include "memory/memoryUtil.hpp"

void * vortexMemory::mallocAligned(size_t alignment, size_t num_bytes)
{
    assert(alignment >= 1 && alignment <= 128);
    assert((alignment & (alignment - 1)) == 0);
    
    uintptr_t rawptr = reinterpret_cast<uintptr_t>(malloc(num_bytes + alignment));
    
    /** Data type is "the fastest data type cloosest to 8 bit on the host architecture. */
    uint_fast8_t diff = alignment - (rawptr & (alignment - 1));
    
    uintptr_t alignPtr = rawptr + diff;
    
    uint_fast8_t * alignMemPtr = reinterpret_cast<uint_fast8_t*>(alignPtr);
    
    *(alignMemPtr - 1) = reinterpret_cast<uint_fast8_t>(diff);
    
    return reinterpret_cast<void*>(alignPtr);
}

void vortexMemory::freeAligned(void* mem_ptr)
{
    uintptr_t alignptr = reinterpret_cast<uintptr_t>(mem_ptr);
    
    uint_fast8_t * alignMemPtr = reinterpret_cast<uint_fast8_t*>(alignptr);
    
    uint_fast8_t diff = *(alignMemPtr - 1);
    
    uintptr_t rawptr = alignptr - diff;
    
    void * raw_addr_ptr = reinterpret_cast<void*>(rawptr);
    
    free(raw_addr_ptr);
}

void vortexMemory::memcpyAlign16(void* src, void* dest, int size_bytes)
{
    assert(sizeof(void* ) == sizeof(float* ));
    
    __m128 xmm0, xmm1, xmm2, xmm3;
    for (int i = 0; i < size_bytes; i+=16)
    {
        xmm0 = _mm_load_ps((float* ) src +  0);
        xmm1 = _mm_load_ps((float* ) src +  4);
        xmm2 = _mm_load_ps((float* ) src +  8);
        xmm3 = _mm_load_ps((float* ) src + 12);
        
        _mm_store_ps((float* ) dest +  0, xmm0);
        _mm_store_ps((float* ) dest +  4, xmm1);
        _mm_store_ps((float* ) dest +  8, xmm2);
        _mm_store_ps((float* ) dest + 12, xmm3);
    }
}

void vortexMemory::memcpyAlign32(void* src, void* dest, int size_bytes)
{
    assert(sizeof(void* ) == sizeof(float* ));
    
    __m256 ymm0, ymm1, ymm2, ymm3;
    for (int i = 0; i < size_bytes; i+=32)
    {
        ymm0 = _mm256_load_ps((float* ) src +  0);
        ymm1 = _mm256_load_ps((float* ) src +  8);
        ymm2 = _mm256_load_ps((float* ) src + 16);
        ymm3 = _mm256_load_ps((float* ) src + 24);
        
        _mm256_store_ps((float* ) dest +  0, ymm0);
        _mm256_store_ps((float* ) dest +  8, ymm1);
        _mm256_store_ps((float* ) dest + 16, ymm2);
        _mm256_store_ps((float* ) dest + 24, ymm3);
    }
}

void vortexMemory::memclearAlign16(void* mem_ptr, int size_bytes)
{
    assert(sizeof(void* ) == sizeof(float* ));
    
    __m128 xmm0 = _mm_set1_ps(0.0f);
    
    for(int i = 0; i < size_bytes; i+=16)
    {
        _mm_store_ps((float* ) mem_ptr +  0, xmm0);
        _mm_store_ps((float* ) mem_ptr +  4, xmm0);
        _mm_store_ps((float* ) mem_ptr +  8, xmm0);
        _mm_store_ps((float* ) mem_ptr + 12, xmm0);
    }
}

void vortexMemory::memclearAlign32(void* mem_ptr, int size_bytes)
{
    assert(sizeof(void* ) == sizeof(float* ));
    
    __m256 ymm0 = _mm256_set1_ps(0.0f);
    
    for (int i = 0; i < size_bytes; i+=32)
    {
        _mm256_store_ps((float* ) mem_ptr +  0, ymm0);
        _mm256_store_ps((float* ) mem_ptr +  8, ymm0);
        _mm256_store_ps((float* ) mem_ptr + 16, ymm0);
        _mm256_store_ps((float* ) mem_ptr + 24, ymm0);
    }
}
