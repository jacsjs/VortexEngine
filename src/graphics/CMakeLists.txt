
set(HEADER_LIST ../../inc/graphics/core/shader.hpp
                ../../inc/graphics/core/renderManager.hpp
                
                ../../inc/graphics/model/mesh.hpp
                
                ../../inc/graphics/scene/scene.hpp
                
                ../../inc/graphics/scene/camera/camera.hpp
                ../../inc/graphics/scene/camera/cameraFirstPerson.hpp
                ../../inc/graphics/scene/camera/cameraOrbit.hpp

)
file(GLOB Sources "core/*.cpp" "model/*.cpp" "scene/*.cpp" "scene/camera/*.cpp")

add_library(vortexgraphics ${Sources} ${HEADER_LIST})

target_include_directories(vortexgraphics PUBLIC "../../inc/")
