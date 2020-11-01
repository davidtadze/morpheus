set(SOURCE_FILES
    MathTest.cpp
)

add_executable(run-math-tests ${SOURCE_FILES})
target_link_libraries(run-math-tests Math gtest gtest_main)

add_test(run-math-tests run-math-tests)
