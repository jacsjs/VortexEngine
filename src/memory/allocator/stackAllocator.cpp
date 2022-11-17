#include "memory/allocator/stackAllocator.hpp"

vortexMemory::StackAllocator::StackAllocator(int alignment, int size_bytes)
: size_bytes(size_bytes)
{
    rawptr = mallocAligned(alignment, size_bytes);
    
    begin_ptr = reinterpret_cast<marker_t>(rawptr);
}

vortexMemory::StackAllocator::~StackAllocator()
{
    freeAligned(reinterpret_cast<void*>(begin_ptr));
}

void vortexMemory::StackAllocator::freeToMarker(vortexMemory::StackAllocator::marker_t begin_ptr)
{
    //TODO
    this->begin_ptr = begin_ptr;
}

void vortexMemory::StackAllocator::clear()
{
    begin_ptr = reinterpret_cast<marker_t>(rawptr);
}
