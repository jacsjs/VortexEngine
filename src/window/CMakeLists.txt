set(HEADER_LIST ../../inc/window/frame.hpp
                ../../inc/window/windowManager.hpp
)
file(GLOB Sources "*.cpp" "windowComponent/*.cpp")

add_library(vortexwindow ${Sources} ${HEADER_LIST})

target_include_directories(vortexwindow PUBLIC "../../inc/")
