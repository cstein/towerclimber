cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(3rd-party)

add_subdirectory(jsonxx)
set(JSONXX_LIBRARIES jsonxx PARENT_SCOPE)

add_subdirectory(pugixml)
set(PUGIXML_LIBRARIES pugixml PARENT_SCOPE)

add_subdirectory(lodepng)
set(LODEPNG_LIBRARIES lodepng PARENT_SCOPE)

# options for bullet3
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared library of")
set(BUILD_UNIT_TESTS OFF CACHE BOOL "Do not build unit tests for bullet.")
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "no bullet2 demos")
set(BUILD_CPU_DEMOS OFF CACHE BOOL "no bullet demos")
set(BUILD_BULLET3 OFF CACHE BOOL "no bullet 3")
add_subdirectory(bullet3)
set(BULLET_LIBRARIES ${BULLET_LIBRARIES} PARENT_SCOPE)

if(ENABLE_TEST)
    message("--- Setting up Google test")
    add_subdirectory(gtest-1.7.0)
    include_directories(${gtest_SOURCE_DIR}/include)

    set(TEST_LIBRARIES
        gtest
        PARENT_SCOPE)
endif(ENABLE_TEST)

