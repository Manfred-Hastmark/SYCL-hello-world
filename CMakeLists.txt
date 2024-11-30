cmake_minimum_required(VERSION 3.30)

project(acpp-hello-world)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_COMPILER acpp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
