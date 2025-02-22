# Locate GTest
find_package (GTest REQUIRED)
include_directories (${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable (
    tests
    main.cpp
    complex_test.cpp
    matrix_test.cpp
    linear_equation_test.cpp
    linear_equation_system_test.cpp
    graph_test.cpp
    basic_network_test.cpp
)
target_link_libraries (tests ${GTEST_LIBRARIES} pthread)