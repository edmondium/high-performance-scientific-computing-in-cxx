cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_VERSION 20)
set(CMAKE_CXX_VERSION_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)
project(ProgrammingInCXX CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(hello hello.cc)
add_executable(control_flow control_flow.cc)

