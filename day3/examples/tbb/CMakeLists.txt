cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(HPCXX CXX)

find_package(TBB REQUIRED)

set (progs 
dasxpcy
dasxpcy_raw_arrays
tbbreduce0
tbbreduce1
)
foreach(prog ${progs})
add_executable(${prog} 	${CMAKE_CURRENT_SOURCE_DIR}/${prog}.cc)
target_link_libraries(${prog} TBB::tbb TBB::tbbmalloc)
endforeach()

