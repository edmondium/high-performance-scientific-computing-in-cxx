cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(TSP-example LANGUAGES CXX)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()
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
target_link_libraries(tsp PUBLIC TBB::tbb TBB::tbbmalloc)

