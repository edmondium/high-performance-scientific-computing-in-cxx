cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(examples CXX)

set(progs 
align0
align1
align2
alignas
alignof
branch_prediction
every_nth
ilp
sfinae0
shim1
stdarray
tag_dispatch
transpose
traverse0
)

foreach(prog ${progs})
add_executable(${prog} ${prog}.cc)
endforeach()

