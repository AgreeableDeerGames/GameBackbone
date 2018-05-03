# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project("GameBackbone")

# project wide output directories
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)

# SFML install path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "E:/Programing/Programing/Cpp/SFML/SFML-2.4.1/cmake/Modules")
set(SFML_ROOT "E:/Programing/Programing/Cpp/SFML/SFML-2.4.1")

# prepend function from https://stackoverflow.com/a/27630120
FUNCTION(PREPEND var prefix)
   SET(listVar "")
   FOREACH(f ${ARGN})
      LIST(APPEND listVar "${prefix}/${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)


add_subdirectory("GameBackboneDll")