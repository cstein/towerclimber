cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(engine)

include(base/CMakeLists.txt)
include(fonts/CMakeLists.txt)
include(renderer/CMakeLists.txt)

set(ENGINE_SRC
    ${BASE_SRC}
    ${FONTS_SRC}
    ${RENDERER_SRC}
    )

add_library(engine
    ${ENGINE_SRC})

set(ENGINE_LIBRARIES
    engine
    PARENT_SCOPE)
