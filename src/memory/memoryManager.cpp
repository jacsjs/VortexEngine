#include "memory/memoryManager.hpp"

#include <iostream>

vortexMemory::MemoryManager::MemoryManager()
{
    pools = new PoolAllocator*[6];
    
    pools[0] = new PoolAllocator(32, 64,  2 * sizeof(float)); //Vec2
    pools[1] = new PoolAllocator(32, 64,  3 * sizeof(float)); //Vec3
    pools[2] = new PoolAllocator(32, 64,  4 * sizeof(float)); //Vec4
    
    pools[3] = new PoolAllocator(32, 16,  4 * sizeof(float)); //Mat2
    pools[4] = new PoolAllocator(32, 16,  9 * sizeof(float)); //Mat3
    pools[5] = new PoolAllocator(32, 16, 16 * sizeof(float)); //Mat4
    
    for (int i = 0; i < sizeof(pools) / sizeof(PoolAllocator*); i++)
    {
        pools[i]->clear();
    }
}

vortexMemory::MemoryManager::~MemoryManager()
{
    for (int i = 0; i < sizeof(pools) / sizeof(PoolAllocator*); i++)
    {
        delete pools[i];
    }
    
    delete [] pools;
}

vortexMemory::MemoryManager & vortexMemory::MemoryManager::instance()
{
    static MemoryManager singleton{};
    return singleton;
}

void vortexMemory::MemoryManager::freePoolMem(vortexMemory::MEMORY_ELEMENT_TYPE type, void* addr)
{
    //std::cout << "Free in freePoolMem: " << reinterpret_cast<uintptr_t>(addr) << ", of type: " << type << std::endl;
    pools[type]->freeChunk(addr);
}

void * vortexMemory::MemoryManager::requestPoolMem(vortexMemory::MEMORY_ELEMENT_TYPE type)
{
    PoolAllocator * currentPool = pools[type];
    if (currentPool->hasFreeChunk())
    {
        void * ret = currentPool->allocChunk();
        //std::cout << "alloc in requestPoolMem: " << reinterpret_cast<uintptr_t>(ret) << ", of type: " << type << std::endl;
        return ret;
    }
    else //If the current pool is full
    {
        PoolAllocator * newPool = new PoolAllocator(currentPool->alignment(), currentPool->capacity() * 2, currentPool->chunkSize());
            
        //TODO: Fix a general memcpyAlign for both 16 and 32
        memcpyAlign32(currentPool->firstAddress(), newPool->firstAddress(), currentPool->capacity() * currentPool->chunkSize());
        
        delete currentPool;
        
        pools[type] = newPool;
        
        return newPool->allocChunk();
    }
}

