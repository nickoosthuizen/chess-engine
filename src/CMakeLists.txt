set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_BUILD_TYPE Debug)

set(SOURCES
  main.cpp
  Move.cpp
  board.cpp
  moveGen.cpp
  utilFunctions.cpp
  perft.cpp
  Game.cpp
  evaluate.cpp
)

add_compile_options(-Wall -Wextra)

add_executable(${BINARY} ${SOURCES})