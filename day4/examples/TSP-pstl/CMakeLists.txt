cmake_minimum_required(VERSION 3.26)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(TSP-example)
include(cmake/CPM.cmake)
CPMAddPackage("gh:bfgroup/Lyra#1.6.1")
find_package(TBB REQUIRED)
add_executable(tsp)
target_sources(tsp
    PUBLIC
    main.cc
)
target_sources(tsp
  PUBLIC
    FILE_SET tsp_module TYPE CXX_MODULES FILES
    TSP.cc
    TSP-Cities.cc
    TSP-Itinerary.cc
)
target_link_libraries(tsp PRIVATE bfg::lyra TBB::tbb TBB::tbbmalloc)

