cmake_minimum_required(VERSION 3.14)

project(Avl_tree)

set(CMAKE_CXX_FLAGS "-std=c++20 -O2 -g")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing() 

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(
  MAIN
  src/main.cpp
)

target_include_directories(MAIN PUBLIC include/)

include(GoogleTest)
