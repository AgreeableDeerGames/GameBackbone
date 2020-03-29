# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)

project("GameBackbone")

include("cmake/Utils/GameBackboneMessage.cmake")

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
gamebackbone_message("current module path: ${CMAKE_MODULE_PATH}")

# set postfix
if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX -d)
endif()

add_subdirectory("GameBackbone")
set(GAME_BACKBONE_INSTALL_TARGETS GameBackbone)

option(GAMEBACKBONE_BUILD_DEMO "Build GameBackbone's demos" OFF)
if(${GAMEBACKBONE_BUILD_DEMO})
	gamebackbone_message("Enabling GameBackbone demo.")
	add_subdirectory("GameBackboneDemo")
	list(APPEND GAME_BACKBONE_INSTALL_TARGETS GameBackboneDemo)
else()
	gamebackbone_message("Disabling GameBackbone demo. Set GAMEBACKBONE_BUILD_DEMO to enable the demo.")
endif()

# optionally build tests
option(GAMEBACKBONE_BUILD_TESTS "Build GameBackbone's test suite" OFF)
if(${GAMEBACKBONE_BUILD_TESTS})
	gamebackbone_message("Enabling GameBackbone unit tests.")
	enable_testing()
	add_subdirectory("GameBackboneUnitTest")
	list(APPEND GAME_BACKBONE_INSTALL_TARGETS GameBackboneUnitTest)
else()
	gamebackbone_message("Disabling GameBackbone unit tests. Set GAMEBACKBONE_BUILD_TESTS to enable the tests.")
endif()


# configure and install
include("${CMAKE_SOURCE_DIR}/cmake/Utils/GBExportAndInstall.cmake")
