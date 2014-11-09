cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(towerclimber)

include(cmake/BuildHelpers.CMakeLists.txt)

set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-reorder")

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(GLEW REQUIRED)

# specific source directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/engine)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party)

add_subdirectory(3rd-party)
add_subdirectory(engine)
add_subdirectory(game)

pre_build(game
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
)
