cmake_minimum_required(VERSION 3.28)
project(4b C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "-g -fsanitize=address,undefined")
set(CMAKE_C_COMPILER "gcc")

add_executable(${PROJECT_NAME} main.c
        splay_tree_dialog.h
        splay_tree_dialog.c
        splay_tree_lib.h
        splay_tree_lib.c
        splay_tree_struct.h
)

target_link_libraries(${PROJECT_NAME} readline)