# CMakeLists for GameBackboneDll's source files
cmake_minimum_required (VERSION 3.8)

add_subdirectory("Backbone")
add_subdirectory("Navigation")
add_subdirectory("Util")

SET(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
