cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(3rd-party)

add_subdirectory(jsonxx)
add_subdirectory(pugixml)
add_subdirectory(lodepng)

if(ENABLE_TEST)
    message("- TESTS are enabled.")
    add_subdirectory(gtest-1.7.0)
    include_directories(${gtest_SOURCE_DIR}/include)
endif(ENABLE_TEST)
