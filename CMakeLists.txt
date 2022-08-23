cmake_minimum_required(VERSION 3.14...3.22)
# ---- Project ----
project(Exemplo VERSION 1.0 LANGUAGES CXX)
set(PROJECT_BIN "exemplo.bin")
include(cmake/all.cmake)

add_subdirectory(source)
add_executable(${PROJECT_BIN} app/main.cpp)
target_link_libraries(${PROJECT_BIN} ${PROJECT_NAME} project_options project_warnings)
