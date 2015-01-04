cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(engine)


set(FADER_SRC
    ${CMAKE_SOURCE_DIR}/tools/python/faders/faders.py)

set(FADER_OUT
    ${CMAKE_CURRENT_SOURCE_DIR}/base/faders.h)

add_custom_command(
    OUTPUT ${FADER_OUT}
    COMMAND python ${FADER_SRC} > ${FADER_OUT}
    DEPENDS ${FADER_SRC})

include(base/CMakeLists.txt)
include(fonts/CMakeLists.txt)
include(game/CMakeLists.txt)
include(renderer/CMakeLists.txt)
include(scenes/CMakeLists.txt)

set(ENGINE_SRC
    ${BASE_SRC}
    ${FONTS_SRC}
    ${GAME_SRC}
    ${RENDERER_SRC}
    ${SCENES_SRC}
    )

add_library(engine
    ${ENGINE_SRC})

set(ENGINE_LIBRARIES
    engine
    PARENT_SCOPE)
