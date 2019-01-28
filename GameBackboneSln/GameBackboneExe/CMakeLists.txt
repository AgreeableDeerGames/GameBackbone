# CMakeLists for GameBackbone demo executable 

cmake_minimum_required (VERSION 3.8)

set(SOURCE_FILES "")

add_subdirectory("source")
add_subdirectory("header")

add_executable(GameBackboneDemo ${SOURCE_FILES})


# link to SFML and TGUI
find_package(SFML 2 REQUIRED network audio graphics window system)
target_link_libraries(GameBackboneDemo sfml-graphics sfml-network sfml-audio sfml-window sfml-system)

find_package(TGUI 0.8.2 REQUIRED)
target_link_libraries(GameBackboneDemo tgui)

find_package(BOX2D REQUIRED)
# I think we should update this to use the keyword PRIVATE. That means updating the rest of our target_link_libraries
target_link_libraries(GameBackboneDemo ${BOX2D_LIBRARY})
include_directories(${BOX2D_INCLUDE_DIR})

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
