cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(HPCXX CXX)
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG -march=native")

find_package(TBB REQUIRED)

set (progs 
transform_reduce
transform_reduce1
transform_reduce2
inner_product
mandelbrot0
birthday_problem
)

foreach(prog ${progs})
add_executable(${prog} 	${CMAKE_CURRENT_SOURCE_DIR}/${prog}.cc)
target_link_libraries(${prog}
		TBB::tbb TBB::tbbmalloc
	)
endforeach()

