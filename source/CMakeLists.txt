include(CMakePrintHelpers)

set (CMAKE_CXX_STANDARD 20)

add_library(
    zcalc_obj OBJECT
    impedance.cpp
    resistor.cpp
    capacitor.cpp
    inductor.cpp
    network.cpp
    source.cpp
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
    include/common.h
    include/reistor.h
    include/capacitor.h
    include/inductor.h
    include/network.h
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