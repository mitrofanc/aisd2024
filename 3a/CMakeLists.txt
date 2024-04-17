cmake_minimum_required(VERSION 3.27)
project(lab3a)
set(CMAKE_C_STANDARD 11)
set(SOURCE_EXE lab3a.c
        lab3afunc.c)
set(SOURCE_LIB lab3alib.c)
set(CMAKE_C_FLAGS "-fsanitize=address,undefined -O0 -g")
set(CMAKE_C_COMPILER "gcc")

option(NDEBUG "Debug" ON)
if(NDEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
endif()

add_library(lab3alib STATIC ${SOURCE_LIB})

add_executable(lab3a ${SOURCE_EXE})

target_link_libraries(lab3a lab3alib)
