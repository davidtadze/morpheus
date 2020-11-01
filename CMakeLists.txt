cmake_minimum_required(VERSION 3.18.0)

project(morpheus)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# enables warnings (as per https://stackoverflow.com/a/14235055)
if (CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif (CMAKE_COMPILER_IS_GNUCC)

set(BUILD_GTEST ON CACHE BOOL "builds the googletest subproject")
set(BUILD_GMOCK ON CACHE BOOL "builds the googlemock subproject")
set(gtest_disable_pthreads ON CACHE BOOL "disables use of pthreads in gtest")
add_subdirectory(third-party/googletest-release-1.8.0)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
