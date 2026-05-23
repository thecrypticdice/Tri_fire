
cmake_minimum_required(VERSION 3.10)

project(Tri_Fire)


add_subdirectory(./3rdParty/raylib)
add_executable(Tri_Fire  ./src/game.cpp)
target_include_directories(Tri_Fire PUBLIC ./src)
target_link_libraries(Tri_Fire  raylib)


