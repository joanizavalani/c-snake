cmake_minimum_required(VERSION 3.28)
project(c_snake C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

if(WIN32)
elseif(APPLE)
elseif(UNIX)
endif()

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(c_snake snake.c snake.h)

target_link_libraries(c_snake ${SDL2_LIBRARY})