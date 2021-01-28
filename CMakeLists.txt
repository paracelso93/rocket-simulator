cmake_minimum_required(VERSION 3.13)
project(rocket)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(rocket main.cpp rocket.cpp rocket.h)
target_link_libraries(rocket SDL2 SDL2_image SDL2_ttf)