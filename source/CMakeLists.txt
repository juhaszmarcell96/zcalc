include(CMakePrintHelpers)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
    zcalc_obj OBJECT
    impedance.cpp
    resistor.cpp
    capacitor.cpp
    inductor.cpp
    network.cpp
    source.cpp
    expression.cpp
    matrix.cpp
)

target_include_directories(
    zcalc_obj INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_include_directories(
    zcalc_obj PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set(
    ZCALC_INCLUDE_FILES
    include/common.hpp
    include/reistor.hpp
    include/capacitor.hpp
    include/inductor.hpp
    include/network.hpp
    include/matrix.hpp
    include/expression.hpp
)

set_target_properties(
    zcalc_obj PROPERTIES
    PUBLIC_HEADER "${ZCALC_INCLUDE_FILES}"
    POSITION_INDEPENDENT_CODE 1
)

add_library(zcalc_shared SHARED)
target_link_libraries(
    zcalc_shared
    PUBLIC zcalc_obj
)

add_library(zcalc_static STATIC)
target_link_libraries(
    zcalc_static
    PUBLIC zcalc_obj
)
