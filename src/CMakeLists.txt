set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_BUILD_TYPE Debug)

set(SOURCES
  main.cpp
  board.cpp
  moveGen.cpp
  utilFunctions.cpp
)

add_executable(${BINARY} ${SOURCES})