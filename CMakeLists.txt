cmake_minimum_required(VERSION 3.10)

project(Life
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-Wpedantic -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-Wpedantic -g -O2")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_THREAD_PREFER_PTHREAD True)
set(THREADS_PREFER_PTHREAD_FLAG True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_PATH "./src")

# Main
add_executable(main "${SRC_PATH}/main.cpp")

add_library(ant "${SRC_PATH}/ant.cpp")

add_library(board "${SRC_PATH}/board.cpp")
target_link_libraries(board ant)

target_link_libraries(main
  ant
  board
  ncurses
  )
