
message("-- Configuring tests")

include_directories(${gtest_SOURCE_DIR}/include)

set(GAME_TEST_LIBRARIES
    ${GAME_LIBRARIES}
    gtest
    )

macro(simple_test TARGET_NAME)
    add_executable(test_${TARGET_NAME} test_${TARGET_NAME}.cc)
    target_link_libraries(test_${TARGET_NAME} ${GAME_TEST_LIBRARIES})
    add_test(NAME ${TARGET_NAME}
             WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
             COMMAND test_${TARGET_NAME})
endmacro()

simple_test(glwindow)
simple_test(sdlwindow)
simple_test(base_scenemanager)
simple_test(base_texturemanager)

simple_test(renderer_rendernode)
simple_test(renderer_textnode)
simple_test(renderer_shader)
simple_test(renderer_shadermanager)
