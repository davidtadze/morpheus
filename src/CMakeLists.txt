include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(math)

set(SOURCE_FILES main.cpp)
add_executable(morpheus ${SOURCE_FILES} ${BACKWARD_ENABLE})
target_link_libraries(morpheus Math)
add_backward(morpheus)