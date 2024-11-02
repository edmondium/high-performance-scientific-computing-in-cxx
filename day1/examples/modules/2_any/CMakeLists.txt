cmake_minimum_required(VERSION 3.26)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(polymorphic_with_any)

add_executable(polyany)
target_sources(polyany
    PUBLIC
    main.cc
)
target_sources(polyany
  PUBLIC
    FILE_SET geometry_modules TYPE CXX_MODULES FILES
    Point.ixx
    Circle.ixx
    Polygon.ixx
    Triangle.ixx
)

