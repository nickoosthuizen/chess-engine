cmake_minimum_required(VERSION 3.16.3)

project(chess-engine)

# for std::popcount
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(tests)