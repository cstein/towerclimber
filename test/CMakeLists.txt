
message("-- Setting up test cases.")
message("--- Google Test: ${gtest_SOURCE_DIR}/include")

include_directories(${gtest_SOURCE_DIR}/include)

add_executable(test_glwindow test_glwindow.cc)
target_link_libraries(test_glwindow
    engine
    jsonxx
    lodepng
    pugixml
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    gtest
    )
add_test(glwindow test_glwindow)

add_executable(test_sdlwindow test_sdlwindow.cc)
target_link_libraries(test_sdlwindow
    engine
    jsonxx
    lodepng
    pugixml
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    gtest
    )
add_test(sdlwindow test_sdlwindow)
