cmake_minimum_required(VERSION 3.20)

set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
project(HPCXX CXX)

find_package(TBB REQUIRED)

set (progs 
dasxpcy
dasxpcy1
dasxpcy_raw_arrays
tbbreduce0
tbbreduce1
nparticle
nparticle_upper_triangle1
)
foreach(prog ${progs})
add_executable(${prog} 	${CMAKE_CURRENT_SOURCE_DIR}/${prog}.cc)
target_link_libraries(${prog} TBB::tbb TBB::tbbmalloc)
endforeach()

