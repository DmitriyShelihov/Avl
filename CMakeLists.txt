# cmake_minimum_required(VERSION 3.14)

# project(Avl_tree)

# set(CMAKE_CXX_FLAGS "-std=c++20 -O2 -g")

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )

# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

# enable_testing() 

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# add_executable(
#   MAIN
#   src/main.cpp
# )

# target_include_directories(MAIN PUBLIC include/)

# include(GoogleTest)

cmake_minimum_required(VERSION 3.14)
project("Avl_tree")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++20 -O2 -g")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(
  AVL_files
  src/main.cpp
)

add_library(avl_lib STATIC ${AVL_files})
target_include_directories(avl_lib PUBLIC include/)

add_executable(AVL src/main.cpp)
target_link_libraries(AVL avl_lib)

###################
#Building tests
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(
  TEST_files
  src/main.cpp
)

add_executable(
  tests_bin
  tests/rofl.cpp
  # tests/rofl2.cpp  
)

add_library(test_lib STATIC ${TEST_files})
target_include_directories(test_lib PUBLIC include/)

target_link_libraries(
  tests_bin
    GTest::gtest_main
    test_lib
)

include(GoogleTest)
gtest_discover_tests(tests_bin)