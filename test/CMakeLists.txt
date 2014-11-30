
message("-- Setting up test cases.")
message("--- Google Test: ${gtest_SOURCE_DIR}/include")

include_directories(${gtest_SOURCE_DIR}/include)

# --- GLWindow ---
add_executable(test_glwindow test_glwindow.cc)
target_link_libraries(test_glwindow
    engine
    jsonxx
    lodepng
    pugixml
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    gtest
    -lGL
    )
add_test(glwindow test_glwindow)

# --- SDLWindow ---
add_executable(test_sdlwindow test_sdlwindow.cc)
target_link_libraries(test_sdlwindow
    engine
    jsonxx
    lodepng
    pugixml
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    gtest
    -lGL
    )
add_test(sdlwindow test_sdlwindow)

# --- RenderNode ---
add_executable(test_renderer_rendernode test_renderer_rendernode.cc)
target_link_libraries(test_renderer_rendernode
    engine
    jsonxx
    lodepng
    pugixml
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    gtest
    -lGL
    )
add_test(renderer_rendernode test_renderer_rendernode)

# --- TextNode ---
add_executable(test_renderer_textnode test_renderer_textnode.cc)
target_link_libraries(test_renderer_textnode
    engine
    jsonxx
    lodepng
    pugixml
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    gtest
    -lGL
    )
add_test(renderer_textnode test_renderer_textnode)

# --- ShaderManager ---
add_executable(test_renderer_shadermanager test_renderer_shadermanager.cc)
target_link_libraries(test_renderer_shadermanager
    engine
    jsonxx
    lodepng
    pugixml
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    gtest
    -lGL
    )
add_test(renderer_shadermanager test_renderer_shadermanager)
