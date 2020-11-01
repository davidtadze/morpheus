include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(math)

set(SOURCE_FILES main.cpp)
add_executable(morpheus ${SOURCE_FILES})
target_link_libraries(morpheus Math)