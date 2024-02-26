set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
    expression_obj OBJECT
    constant.cpp
    operation.cpp
    variable.cpp
    variable_pool.cpp
    term_factory.cpp
    expression.cpp
)

target_include_directories(
    expression_obj INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_include_directories(
    expression_obj PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include
)

set(
    EXPRESSION_INCLUDE_FILES
    zcalc/expression/term.hpp
    zcalc/expression/constant.hpp
    zcalc/expression/operation.hpp
    zcalc/expression/variable.hpp
    zcalc/expression/variable_pool.hpp
    zcalc/expression/term_factory.hpp
    zcalc/expression/expression.hpp
)

set_target_properties(
    expression_obj PROPERTIES
    PUBLIC_HEADER "${EXPRESSION_INCLUDE_FILES}"
    POSITION_INDEPENDENT_CODE 1
)

add_library(expression_shared SHARED)
target_link_libraries(
    expression_shared
    PUBLIC expression_obj
)

add_library(expression_static STATIC)
target_link_libraries(
    expression_static
    PUBLIC expression_obj
)