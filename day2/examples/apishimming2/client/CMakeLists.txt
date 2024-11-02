cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(examples CXX)
set(PACKAGE_DIR "${PROJECT_SOURCE_DIR}/libs")

set(CMAKE_CXX_FLAGS "-stdlib=libc++ -fmodules -fprebuilt-module-path=${PACKAGE_DIR} ${CMAKE_CXX_FLAGS}")

add_executable(callalgo main.cc)
add_custom_target(MyGreatProduct DEPENDS "${PACKAGE_DIR}/MyGreatProduct.pcm")
add_dependencies(callalgo MyGreatProduct)


