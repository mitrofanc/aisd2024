cmake_minimum_required(VERSION 3.15)
project(lab2)
set(CMAKE_C_STANDARD 99)
set(SOURCE_EXE lab2.c)
set(SOURCE_LIB deck.c)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -fsanitize=address,undefined -O0 ")
set(CMAKE_C_COMPILER "gcc")

option(TYPE "Type of data structure" ON)
if(TYPE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDECK_TYPE=1")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDECK_TYPE=0")
endif()

option(NDEBUG "Debug" ON)
if(NDEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
endif()

option(SOD "Static or dynamic" ON)
if(SOD)
    add_library(deck STATIC ${SOURCE_LIB})
else()
    add_library(deck SHARED ${SOURCE_LIB})
endif()

add_executable(lab2 ${SOURCE_EXE})

target_link_libraries(lab2 deck)

