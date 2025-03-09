cmake_minimum_required(VERSION 3.31.6)
project(rlibSnakeGame VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib CONFIG REQUIRED)
add_executable(rlibSnakeGame main.cpp)
target_link_libraries(rlibSnakeGame PRIVATE raylib)