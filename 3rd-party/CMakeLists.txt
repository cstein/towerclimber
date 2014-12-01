cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(3rd-party)

add_subdirectory(jsonxx)
add_subdirectory(pugixml)
add_subdirectory(lodepng)

SET(BUILD_SHARED_LIBS OFF CACHE BOOL "Build libfoo shared library")
set(BUILD_UNIT_TESTS OFF CACHE BOOL "Do not build unit tests.")
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "no bullet2 demos")
set(BUILD_CPU_DEMOS OFF CACHE BOOL "no bullet demos")
set(BUILD_BULLET3 OFF CACHE BOOL "no bullet 3")

add_subdirectory(bullet3)

if(ENABLE_TEST)
    message("- TESTS are enabled.")
    add_subdirectory(gtest-1.7.0)
    include_directories(${gtest_SOURCE_DIR}/include)
endif(ENABLE_TEST)


