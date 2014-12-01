cmake_minimum_required(VERSION 2.8)

set(GAME_SRC
    main.cc)

add_executable(game ${GAME_SRC})

target_link_libraries(game
    engine
    ${BULLET_LIBRARIES}
    ${JSONXX_LIBRARIES}
    ${LODEPNG_LIBRARIES}
    ${PUGIXML_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    -lGL)

