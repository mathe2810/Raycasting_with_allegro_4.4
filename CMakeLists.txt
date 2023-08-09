cmake_minimum_required(VERSION 3.23)
project(ProjetPerso3dEngine2 C)

set(CMAKE_C_STANDARD 99)

add_executable(ProjetPerso3dEngine2 main.c textures/All_Textures.h textures/sky.h textures/sprites.h textures/won.h textures/title.h textures/lost.h textures/sprites_2.h)

target_link_libraries(ProjetPerso3dEngine2 -lalleg44 -lmingw32)
