cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_BUILD_TYPE debug)

set (
    EXAMPLES
    basic
    lora_filter
    rc_element
    bandpass
    lc_filter
    capacitor
    bluetooth
)

include_directories("../include/")

foreach (example ${EXAMPLES})
    add_executable(${example} ${example}/${example}.cpp)
endforeach()

add_custom_target(examples ALL DEPENDS ${EXAMPLES})