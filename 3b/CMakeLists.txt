cmake_minimum_required(VERSION 3.27)
project(lab3b_AaDS C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "-g -fsanitize=address,undefined")
set(CMAKE_C_COMPILER "gcc")

add_executable(${PROJECT_NAME} main.c
        hash_table_lib.h
        hash_table.h
        hash_table_lib.c
        hash_table_func.h
        hash_table_func.c
)

target_link_libraries(${PROJECT_NAME} readline)