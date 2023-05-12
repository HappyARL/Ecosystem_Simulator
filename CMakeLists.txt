cmake_minimum_required(VERSION 3.2)
project(Game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_OSX_ARCHITECTURES "x86_64")

set(
        SOURCE_FILES
        main.cpp
        Game.h Game.cpp
        State.cpp State.h
        GameState.cpp GameState.h
        Entity.cpp Entity.h
        MainMenuState.cpp MainMenuState.h Button.cpp Button.h Player.cpp Player.h MapGenerator.cpp MapGenerator.h PerlinNoise.cpp PerlinNoise.h Pig.cpp Pig.h PauseMenuState.cpp PauseMenuState.h aStarAlgoritm.cpp aStarAlgoritm.h Wolf.cpp Wolf.h)

add_executable(Game ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Game ${SFML_LIBRARIES})
endif()