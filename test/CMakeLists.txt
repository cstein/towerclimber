
message("-- Setting up test cases.")
message("--- Google Test: ${gtest_SOURCE_DIR}/include")

include_directories(${gtest_SOURCE_DIR}/include)


set(GAME_LIBS
    engine
    jsonxx
    lodepng
    pugixml
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    -lGL
    )

set(GAME_TEST_LIBS
    ${GAME_LIBS}
    gtest
    )

macro(simple_test TARGET_NAME)
    add_executable(test_${TARGET_NAME} test_${TARGET_NAME}.cc)
    target_link_libraries(test_${TARGET_NAME} ${GAME_TEST_LIBS})
    add_test(${TARGET_NAME} test_${TARGET_NAME})
endmacro()

simple_test(glwindow)
simple_test(sdlwindow)

simple_test(renderer_rendernode)
simple_test(renderer_textnode)
simple_test(renderer_shader)
simple_test(renderer_shadermanager)
