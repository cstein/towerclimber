cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(towerclimber)
option(ENABLE_TESTS "Build all tests." OFF)

include(cmake/BuildHelpers.CMakeLists.txt)

set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-reorder")

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

set(GFX_LIBRARIES
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES})

include_directories(${SDL2_INCLUDE_DIRS})

# specific source directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/engine)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party)

message("-- Configuring 3rd-party libraries")
add_subdirectory(3rd-party)
set(THIRDPARTY_LIBRARIES
    ${JSONXX_LIBRARIES}
    ${PUGIXML_LIBRARIES}
    ${LODEPNG_LIBRARIES}
    ${BULLET_LIBRARIES})

message("-- Configuring game engine")
add_subdirectory(engine)
message("-- Configuring game")
set(GAME_LIBRARIES
    ${ENGINE_LIBRARIES}
    ${THIRDPARTY_LIBRARIES}
    ${GFX_LIBRARIES})
add_subdirectory(game)

if(ENABLE_TEST)
    add_definitions(-DENABLE_TEST)
    enable_testing()
    add_subdirectory(test)
endif(ENABLE_TEST)

pre_build(game
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
)
