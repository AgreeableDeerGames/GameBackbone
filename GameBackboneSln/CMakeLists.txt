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
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)

# SFML and TGUI install path
if (NOT $ENV{SFML_ROOT} STREQUAL "")
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{SFML_ROOT}/cmake/Modules)
	set(SFML_ROOT $ENV{SFML_ROOT})
endif()
if (NOT $ENV{TGUI_ROOT} STREQUAL "")
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{TGUI_ROOT}/cmake/Modules)
	set(TGUI_ROOT $ENV{TGUI_ROOT})
endif()

# prepend function from https://stackoverflow.com/a/27630120
FUNCTION(PREPEND var prefix)
   SET(listVar "")
   FOREACH(f ${ARGN})
      LIST(APPEND listVar "${prefix}/${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)


add_subdirectory("GameBackboneLib")
add_subdirectory("GameBackboneExe")
add_subdirectory("GameBackboneBoostUnitTest1")