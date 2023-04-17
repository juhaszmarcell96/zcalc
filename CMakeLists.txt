cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 20)

project(
    CircuitSimulator
    VERSION 00.00.01
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# add source as subdirectory and name it bin in the build directory
add_subdirectory(source bin)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(cppsim main.cpp)

target_link_libraries(cppsim zcalc_static)