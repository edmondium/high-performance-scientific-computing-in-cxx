cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (TSP_USE_IMPORT_STD)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
endif()
project(TSP VERSION 2.0.1 LANGUAGES CXX)

if (TSP_USE_IMPORT_STD)
set(CMAKE_CXX_MODULE_STD 1 CACHE STRING "Whether or not to use C++23 import std; while building")
  add_definitions("-DUSE_IMPORT_STD=${TSP_USE_IMPORT_STD}")
endif()

add_executable(tsp)
target_sources(tsp
    PUBLIC
    main.cc
)
target_sources(tsp
  PUBLIC
    FILE_SET tsp_module TYPE CXX_MODULES FILES
    TSP.ixx
    TSP-Cities.ixx
    TSP-Itinerary.ixx
)

