cmake_minimum_required(VERSION 3.10)

project(polymorphic_w_any CXX)
set(CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set(Headers Point.hh Polygon.hh Triangle.hh Circle.hh)
add_executable(${PROJECT_NAME} Point.cc Triangle.cc Circle.cc main.cc ${Headers})

