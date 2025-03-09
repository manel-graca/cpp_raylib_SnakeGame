cmake_minimum_required(VERSION 3.31.6)
project(cpp-rlib-snake VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib CONFIG REQUIRED)
add_executable(cpp-rlib-snake main.cpp)
target_link_libraries(cpp-rlib-snake PRIVATE raylib)
