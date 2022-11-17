#include "memory/allocator/poolAllocator.hpp"

vortexMemory::PoolAllocator::PoolAllocator(int alignment, int num_chunks, int chunkSize_bytes)
: poolAlignment(alignment), chunkSize_bytes(chunkSize_bytes), num_chunks(num_chunks)
{
    assert(chunkSize_bytes >= minChunkSize() && "Chunk size too small in poolAllocator");
    assert(num_chunks >= 1);
    
    first_chunk = reinterpret_cast<uintptr_t>(aligned_alloc(alignment, chunkSize_bytes * num_chunks));
    
    assert(first_chunk != 0); //Make sure requested memory was allocated.
    
    begin_ptr = first_chunk;
    last_chunk = begin_ptr + (chunkSize_bytes * (num_chunks - 1));;

    this->clear();
}

vortexMemory::PoolAllocator::~PoolAllocator()
{
    free(reinterpret_cast<void*>(first_chunk));
}

void * vortexMemory::PoolAllocator::allocChunk()
{
    uintptr_t ret_ptr = begin_ptr;
    uintptr_t next_addr = *(reinterpret_cast<uintptr_t*>(begin_ptr)); //value stored in the pointer is the address of next element
    
    if (next_addr != 0)
    {
        begin_ptr = next_addr;
    }
    else
    {
        begin_ptr = 0;
    }
    
    //Delete next pointer (in case it is added again without overwriting the value, causeing an ifinite cycle)
    *(reinterpret_cast<uintptr_t*>(ret_ptr)) = 0;
    
    return reinterpret_cast<void*>(ret_ptr);
}
void vortexMemory::PoolAllocator::freeChunk(void* chunk_ptr)
{
    assert(resideInPool(chunk_ptr) && "Invalid pointer given to function freeChunk(void* chunk_ptr) in poolAllocator");
    
    uintptr_t new_ptr = reinterpret_cast<uintptr_t>(chunk_ptr);

    if (new_ptr > begin_ptr) //Insertion at the end
    {
       *(reinterpret_cast<uintptr_t*>(new_ptr)) = begin_ptr;
       begin_ptr = new_ptr;
    }
    else //Insertion between elements
    {
        *(reinterpret_cast<uintptr_t*>(new_ptr)) = *(reinterpret_cast<uintptr_t*>(begin_ptr)); //point this pointer to the "replacement" pointed element
        *(reinterpret_cast<uintptr_t*>(begin_ptr)) = new_ptr;                                  //set the last pointer to point to this;
    }
    
}


void vortexMemory::PoolAllocator::clear()
{
    assert(first_chunk != 0);
    begin_ptr = first_chunk;
    
    for (int i = 1; i < num_chunks; i++)
    {
        freeChunk(reinterpret_cast<void*>(begin_ptr + chunkSize_bytes));
    }
}

bool vortexMemory::PoolAllocator::resideInPool(void* mem_ptr)
{
    //NOTE: Works now
    uintptr_t u_mem_ptr = reinterpret_cast<uintptr_t>(mem_ptr);
    return u_mem_ptr <= last_chunk && u_mem_ptr >= first_chunk;
}

int vortexMemory::PoolAllocator::spaceRemaining()
{
    //TODO
    return 0;
}

int vortexMemory::PoolAllocator::minChunkSize()
{
    return sizeof(uintptr_t);
}
