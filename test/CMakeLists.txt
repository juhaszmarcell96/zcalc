# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(
    tests
    main.cpp
    matrix_test.cpp
)
target_link_libraries(tests ${GTEST_LIBRARIES} pthread zcalc_static)