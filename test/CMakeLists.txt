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
    edge_test.cpp
    path_test.cpp
    graph_test.cpp
    network_calculator_test.cpp
    symbolic_linear_equation_test.cpp
    json_test.cpp
    network_json_test.cpp
)
target_link_libraries (tests ${GTEST_LIBRARIES} pthread)