# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)

project(GameBackboneProject VERSION 0.4.0)

include("cmake/Utils/GameBackboneMessage.cmake")

# project wide output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE PATH "Output directory for built archive files")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE PATH "Output directory for built library files")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE PATH "Output directory for built binary files")

# add custom modules to path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/Modules)
gamebackbone_message("current module path: ${CMAKE_MODULE_PATH}")

# set postfix
if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX -d)
endif()

add_subdirectory("GameBackbone")

# optionally build demo
option(GAMEBACKBONE_BUILD_DEMO "Build GameBackbone's demos" OFF)
if(${GAMEBACKBONE_BUILD_DEMO})
	gamebackbone_message("Enabling GameBackbone demo.")
	add_subdirectory("Demo")
else()
	gamebackbone_message("Disabling GameBackbone demo. Set GAMEBACKBONE_BUILD_DEMO to enable the demo.")
endif()

# optionally build tests
option(GAMEBACKBONE_BUILD_TESTS "Build GameBackbone's test suite" OFF)
if(${GAMEBACKBONE_BUILD_TESTS})
	gamebackbone_message("Enabling GameBackbone unit tests.")
	enable_testing()
	add_subdirectory("Tests")
else()
	gamebackbone_message("Disabling GameBackbone unit tests. Set GAMEBACKBONE_BUILD_TESTS to enable the tests.")
endif()

# ensure resources like textures are available for the executables
if(${GAMEBACKBONE_BUILD_DEMO} OR ${GAMEBACKBONE_BUILD_TESTS})
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources/TestFiles DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Textures DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources/TGUI_Widgets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
