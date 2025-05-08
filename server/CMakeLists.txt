cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_BUILD_TYPE debug)

# Require Boost 1.66 or higher (for Boost.Beast)
find_package(Boost 1.66 REQUIRED COMPONENTS system)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found or version too low (need >= 1.66)")
endif()

add_executable(server main.cpp server.cpp session.cpp)
include_directories("../include/")
target_include_directories(server PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(server PRIVATE Boost::system pthread)
