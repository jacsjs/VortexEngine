set(CMAKE_CXX_FLAGS "-fPIC" "-lpthread")

file(GLOB Sources "*.cpp")

include_directories(../inc/)

include_directories(/usr/include/GLFW/)

link_directories(/usr/lib64/)

add_subdirectory(memory/)
add_subdirectory(window/)
add_subdirectory(graphics/)
add_subdirectory(input/)
add_subdirectory(math/)


add_executable(vortexengine ${Sources} "glad/glad.c")

target_link_libraries(vortexengine PRIVATE vortexmemory vortexwindow vortexgraphics vortexinput vortexmath glfw GL X11 pthread Xrandr Xi dl)

