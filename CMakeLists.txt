cmake_minimum_required(VERSION 3.10)

project(QuizletTesting)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(screenshot screenshot.cpp)

add_executable(resize resize.cpp)
target_include_directories(resize PRIVATE resize.cpp)
