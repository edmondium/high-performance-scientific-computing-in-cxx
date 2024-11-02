cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
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
target_link_libraries(tsp PRIVATE TBB::tbb TBB::tbbmalloc)

