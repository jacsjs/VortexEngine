
set(HEADER_LIST ../../inc/math/alignedVector.hpp
                ../../inc/math/mat.hpp 
                ../../inc/math/quaternion.hpp 
                ../../inc/math/vec.hpp 
                ../../inc/math/vecSOA.hpp
)
file(GLOB Sources "*.cpp")

add_library(vortexmath ${Sources} ${HEADER_LIST})

target_include_directories(vortexmath PUBLIC "../../inc/")

#target_link_libraries(vortexgraphics PRIVATE Boost::boost)

