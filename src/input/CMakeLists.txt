
set(HEADER_LIST ../../inc/input/inputManager.hpp
                
                ../../inc/input/inputMapping/abstractInputMapping.hpp 
                ../../inc/input/inputMapping/defaultInputMapping.hpp 
                
                ../../inc/input/inputCommandFactory/inputCommandFactory.hpp
                
                ../../inc/input/inputCommands/abstractInputCommand.hpp 
                ../../inc/input/inputCommands/nullInputCommand.hpp
                
                ../../inc/input/inputCommands/cameraCommands/cameraLeftCommand.hpp
                ../../inc/input/inputCommands/cameraCommands/cameraLeftCommand.hpp
                ../../inc/input/inputCommands/cameraCommands/cameraDownCommand.hpp
                ../../inc/input/inputCommands/cameraCommands/cameraUpCommand.hpp
                ../../inc/input/inputCommands/cameraCommands/cameraInCommand.hpp
                ../../inc/input/inputCommands/cameraCommands/cameraOutCommand.hpp
)
file(GLOB Sources "*.cpp" "inputCommands/*.cpp" "inputCommands/cameraCommands/*.cpp" "inputMapping/*.cpp" "inputCommandFactory/*.cpp")

add_library(vortexinput ${Sources} ${HEADER_LIST})

target_include_directories(vortexinput PUBLIC "../../inc/")

#target_link_libraries(vortexgraphics PRIVATE Boost::boost)

