cmake_minimum_required(VERSION 3.23)
project(ProjetPerso3dEngine2 C)

set(CMAKE_C_STANDARD 99)

add_executable(ProjetPerso3dEngine2 main.c All_Textures.h sky.h sprites.h won.h title.h lost.h)

target_link_libraries(ProjetPerso3dEngine2 -lalleg44 -lmingw32)
