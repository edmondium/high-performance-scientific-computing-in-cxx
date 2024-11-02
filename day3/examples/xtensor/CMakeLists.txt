cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(xtensor_examples CXX)

find_package(xtl REQUIRED)
find_package(xtensor REQUIRED)
find_package(xsimd REQUIRED)
find_package(Threads REQUIRED)
set(BLA_VENDOR OpenBLAS)
find_package(BLAS)

set(progs xt0 xt1 xt2)

foreach(prog ${progs})
    add_executable(${prog} ${prog}.cc)
    target_link_libraries(${prog} xtensor xtensor::optimize xtensor::use_xsimd
	    BLAS::BLAS 
	    #Threads::Threads gfortran
	  )
endforeach()

