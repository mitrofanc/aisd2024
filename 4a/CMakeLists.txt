
#cmake_minimum_required(VERSION 3.27)
#project(4a C)
#
#set(CMAKE_C_STANDARD 11)
#target_link_libraries(readline)
#
#add_executable(4a
#        main.c
#        bintree_lib.c
#        bintree_lib.h
#        bintree_dialog.h
#        bintree_dialog.c
#        bintree_struct.h)

cmake_minimum_required(VERSION 3.27)
project(4a C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "-g -fsanitize=address,undefined")
set(CMAKE_C_COMPILER "gcc")

add_executable(${PROJECT_NAME} main.c
        bintree_dialog.h
        bintree_dialog.c
        bintree_lib.h
        bintree_lib.c
        bintree_struct.h
)

target_link_libraries(${PROJECT_NAME} readline)