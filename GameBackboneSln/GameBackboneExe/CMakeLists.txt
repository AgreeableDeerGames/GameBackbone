# CMakeLists for GameBackbone demo executable 

cmake_minimum_required (VERSION 3.8)

set(SOURCE_FILES "")

add_subdirectory("source")
add_subdirectory("header")

add_executable(GameBackboneDemo ${SOURCE_FILES})
find_package(SFML 2 REQUIRED network audio graphics window system)

# link to SFML and TGUI
if(SFML_FOUND)
  target_link_libraries(GameBackboneDemo sfml-graphics sfml-network sfml-audio sfml-window sfml-system)
endif()


find_package(TGUI 0.8.2 REQUIRED)
if(TGUI_FOUND)
  target_link_libraries(GameBackboneDemo tgui)
endif()

# This is how to link to GB if it was being built from a different CMake process
# find_package(GameBackbone REQUIRED) 
# if(GB_FOUND) 
#   include_directories(${GB_INCLUDE_DIR}) 
#   target_link_libraries(GameBackboneDemo ${GB_LIBRARY}) 
# endif() 

include_directories(${GB_INCLUDE_DIR})
target_link_libraries(GameBackboneDemo GameBackbone)

# Include own header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/header)
