set(BINARY ${CMAKE_PROJECT_NAME}_test)

set(SOURCES 
  main.cpp
  boardTests.cpp
  moveGenTests.cpp
  ../src/moveGen.cpp
  ../src/board.cpp 
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(${BINARY} ${SOURCES})
target_link_libraries(${BINARY} gtest_main)
include_directories(../src)

include(GoogleTest)
gtest_discover_tests(${BINARY})
