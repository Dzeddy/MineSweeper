cmake_minimum_required(VERSION 3.23)
project(Project4V2)
include_directories("C:/Libraries/SFML-2.5.1/include")
set(CMAKE_CXX_STANDARD 14)
set(SFML_STATIC_LIBRARIES TRUE)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Project4V2 MineSweeper.cpp Toolbox.cpp Toolbox.h Button.cpp Button.h Tile.cpp Tile.h GameState.cpp GameState.h Minesweeper.cpp Toolbox.cpp Toolbox.h Button.cpp Button.h Tile.cpp Tile.h GameState.cpp GameState.h Minesweeper.h)
target_link_libraries(Project4V2 sfml-graphics sfml-audio)
