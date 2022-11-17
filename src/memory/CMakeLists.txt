
set(HEADER_LIST ../../inc/memory/memoryManager.hpp
                ../../inc/memory/memoryUtil.hpp 
                ../../inc/memory/allocator/poolAllocator.hpp 
                ../../inc/memory/allocator/stackAllocator.hpp 
                ../../inc/memory/allocator/doubleEndedStackAllocator.hpp
)
file(GLOB Sources "*.cpp" "allocator/*.cpp")

add_library(vortexmemory ${Sources} ${HEADER_LIST})

target_include_directories(vortexmemory PUBLIC "../../inc/")

