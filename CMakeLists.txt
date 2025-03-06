cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_BUILD_TYPE debug)

project (
    zcalc
    VERSION 00.00.01
    LANGUAGES CXX
)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory (test)
add_subdirectory (examples)
add_subdirectory (benchmark)
