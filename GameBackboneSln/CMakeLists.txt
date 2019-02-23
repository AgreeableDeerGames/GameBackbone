# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)

project("GameBackbone")

# top project folder
set(GAMEBACKBONE_TOP_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})

# project wide output directories
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(GB_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)

# add custom modules to path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${GAMEBACKBONE_TOP_FOLDER}/cmake/Modules)
message("cmake module path :" ${CMAKE_MODULE_PATH})

# set posfix
if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX -d)
endif()

add_subdirectory("GameBackbone")
add_subdirectory("GameBackboneDemo")
add_subdirectory("GameBackboneUnitTest")
