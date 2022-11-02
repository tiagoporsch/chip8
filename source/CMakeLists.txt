add_library(${PROJECT_NAME}
	chip8/cpu.cpp
	chip8/emulator.cpp
	chip8/keyboard.cpp
	chip8/memory.cpp
	chip8/registers.cpp
	chip8/screen.cpp
	chip8/stack.cpp
	chip8/timer.cpp
	gui/sfml.cpp
)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})
                    
#Sobre numeração de versão
#https://semver.org
                    
set_target_properties(${PROJECT_NAME} PROPERTIES 
SOVERSION   1
VERSION     1.0.0
)
                    
target_include_directories(${PROJECT_NAME}
PUBLIC
$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>
)

target_link_libraries(
${PROJECT_NAME}
PRIVATE project_options
project_warnings
)

