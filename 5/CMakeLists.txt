cmake_minimum_required(VERSION 3.28)
project(5 C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "-g -fsanitize=address,undefined")
set(CMAKE_C_COMPILER "gcc")

add_executable(${PROJECT_NAME} main.c
        graph_dialog.h
        graph_dialog.c
        graph_lib.h
        graph_lib.c
        graph_struct.h
        queue.h
        queue.c
)

target_link_libraries(${PROJECT_NAME} readline)
