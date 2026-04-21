cmake_minimum_required(VERSION 3.10)
project(problem_024_deque CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(code src/main.cpp)
target_include_directories(code PRIVATE ${CMAKE_SOURCE_DIR})

