cmake_minimum_required(VERSION 3.0)

project(vortexengine)

add_subdirectory(src/)

install(TARGETS vortexengine RUNTIME DESTINATION bin)
