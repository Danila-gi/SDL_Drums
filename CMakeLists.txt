cmake_minimum_required(VERSION 3.10)

project(SDL_project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(game src/main.cpp src/mainwindow.h src/mainwindow.cpp src/rotationbutton.h src/rotationbutton.cpp
               src/fontscontainer.h src/fontscontainer.cpp src/drumsmodel.h src/drumsmodel.cpp
               src/drumsview.h src/drumsview.cpp)

target_link_libraries(game PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf)