cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(engine)

include(base/CMakeLists.txt)
include(fonts/CMakeLists.txt)

set(ENGINE_SRC
    ${BASE_SRC}
    ${FONTS_SRC}
    )

add_library(engine
    ${ENGINE_SRC})
