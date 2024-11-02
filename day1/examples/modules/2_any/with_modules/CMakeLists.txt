cmake_minimum_required(VERSION 3.18)

project(polymorphic_w_any CXX)
set(CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-fmodules HAS_FMODULES)
if (HAS_FMODULES)
    set(COMPILE_FLAGS -fmodules ${COMPILE_FLAGS})
else()
    check_cxx_compiler_flag(-fmodules-ts HAS_FMODULES_TS)
    if (HAS_FMODULES_TS)
        set(COMPILE_FLAGS -fmodules-ts ${COMPILE_FLAGS})
    else()
        message(FATAL_ERROR "This compiler does not have either of the options -fmodules or -fmodules-ts!")
    endif()
endif()
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
if (NOT CMI_CACHE)
        set(CMI_CACHE ${PROJECT_BINARY_DIR}/pcm.cache)
endif()
	set(CMI_EXT ".pcm")
        set(COMPILE_FLAGS ${COMPILE_FLAGS} -std=c++20 -stdlib=libc++ -fbuiltin-module-map -fprebuilt-module-path=${CMI_CACHE})
        set(MIFC_BUILD_FLAGS ${COMPILE_FLAGS} ${CMAKE_CXX_FLAGS} --precompile -xc++-module)
        set(MIMP_BUILD_FLAGS ${COMPILE_FLAGS} ${CMAKE_CXX_FLAGS} -xc++ -c)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
if (NOT CMI_CACHE)
        set(CMI_CACHE ${PROJECT_BINARY_DIR}/gcm.cache)
endif()
	set(CMI_EXT ".gcm")
    message(STATUS "Generating standard library header units.")
        execute_process(COMMAND ${PROJECT_SOURCE_DIR}/make_gcm_cache.sh
                WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
                OUTPUT_VARIABLE CMI_CACHE
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    message(STATUS "Done.")
    set(MIFC_BUILD_FLAGS ${COMPILE_FLAGS} ${CMAKE_CXX_FLAGS} -std=c++20 -c -xc++)
    set(MIMP_BUILD_FLAGS ${COMPILE_FLAGS} ${CMAKE_CXX_FLAGS})
else()
    message(FATAL_ERROR "Unsupported compiler ...")
endif()
file(MAKE_DIRECTORY ${CMI_CACHE})
set(ADDITIONAL_CLEAN_FILES ${CMI_CACHE})

function(module_interface out_var)
  set(result)
  foreach(in_f ${ARGN})
    file(RELATIVE_PATH out_f ${CMAKE_CURRENT_SOURCE_DIR} ${in_f})
    string(REGEX REPLACE "[.]ixx$" ${CMI_EXT} out_f ${out_f})
    set(out_f "${CMI_CACHE}/${out_f}")
    add_custom_command(OUTPUT ${out_f}
            COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -o ${out_f} ${MIFC_BUILD_FLAGS} ${in_f}
      DEPENDS ${in_f}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Creating module interface file ${out_f}"
      VERBATIM
      )
    list(APPEND result ${out_f})
  endforeach()
  set(${out_var} "${result}" PARENT_SCOPE)
endfunction()

module_interface(mod_Point ${CMAKE_CURRENT_SOURCE_DIR}/Point.ixx)
module_interface(mod_Circle ${CMAKE_CURRENT_SOURCE_DIR}/Circle.ixx)
module_interface(mod_Polygon ${CMAKE_CURRENT_SOURCE_DIR}/Polygon.ixx)
module_interface(mod_Triangle ${CMAKE_CURRENT_SOURCE_DIR}/Triangle.ixx)

set(mods ${mod_Point} ${mod_Circle} ${mod_Polygon} ${mod_Triangle})
add_library(shapes
        ${mods} 
	Point.ixx
	Circle.ixx
	Polygon.ixx
	Triangle.ixx
)
target_compile_options(shapes PRIVATE ${MIMP_BUILD_FLAGS})
add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} shapes)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_FLAGS})

