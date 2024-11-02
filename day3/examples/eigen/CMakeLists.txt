cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(HPCXX CXX)
set (CMAKE_BUILD_TYPE Release)

find_package(OpenMP REQUIRED)

set (progs eigen0 eigen1 eigen1b matmul mattrans)
foreach(prog ${progs})
add_executable(${prog} 			${CMAKE_CURRENT_SOURCE_DIR}/${prog}.cc)
target_include_directories(${prog} PRIVATE $ENV{EIGEN3_INCLUDE_DIR})
target_compile_options(${prog} PRIVATE -march=native)
target_link_libraries(${prog} PRIVATE OpenMP::OpenMP_CXX)
endforeach()

