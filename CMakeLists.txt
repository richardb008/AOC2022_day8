cmake_minimum_required(VERSION 3.13)

project(aoc22_8)

set(CMAKE_CXX_STANDARD 17)

add_executable(aoc22_8 
main.cpp
ForestAnalyzer.h
ForestAnalyzer.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall -Wextra -Wpedantic
)