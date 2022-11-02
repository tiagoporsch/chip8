cmake_minimum_required(VERSION 3.14...3.22)

project(Chip8 VERSION 1.0 LANGUAGES CXX)
set(PROJECT_BIN "chip8")
include(cmake/all.cmake)

add_subdirectory(source)
add_executable(${PROJECT_BIN} app/main.cpp)

find_package(SFML 2.5 COMPONENTS audio graphics REQUIRED)
target_link_libraries(${PROJECT_BIN} ${PROJECT_NAME} project_options project_warnings sfml-audio sfml-graphics)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
)
add_dependencies(${PROJECT_BIN} copy_assets)