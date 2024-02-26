find_package (GTest REQUIRED)
include_directories (${GTEST_INCLUDE_DIRS})
 
add_executable (
    expression_tests
    main.cpp
    constant_test.cpp
    variable_test.cpp
    operation_test.cpp
    expression_test.cpp
)
target_link_libraries (expression_tests ${GTEST_LIBRARIES} pthread expression_static)