cmake_minimum_required(VERSION 3.16.3)

project(chess-engine)

add_executable(chess main.cpp)

add_subdirectory(src)
include_directories(src)