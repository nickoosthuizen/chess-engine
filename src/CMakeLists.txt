set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
  main.cpp
  board.cpp
  moveGen.cpp
)

add_executable(${BINARY} ${SOURCES})