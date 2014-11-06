cmake_minimum_required(VERSION 2.8)

set(GAME_SRC
    main.cc)

add_executable(game ${GAME_SRC})
target_link_libraries(game
    engine
    jsonxx
    lodepng
    pugixml
    ${SDL2_LIBRARIES})

