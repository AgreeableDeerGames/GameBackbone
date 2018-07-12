# CMakeLists for GameBackbone demo executable 

cmake_minimum_required (VERSION 3.8)

set(SOURCE_FILES "")

add_subdirectory("source")
add_subdirectory("header")

add_executable(GameBackboneDemo ${SOURCE_FILES})
find_package(SFML 2 REQUIRED network audio graphics window system)

# link to SFML and TGUI
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(GameBackboneDemo sfml-graphics sfml-network sfml-audio sfml-window sfml-system)
endif()


find_package(TGUI 0.7.7 REQUIRED)
if(TGUI_FOUND)
  include_directories(${TGUI_INCLUDE_DIR})
  target_link_libraries(GameBackboneDemo ${TGUI_LIBRARY})
endif()

include_directories(${GB_INCLUDE_DIR})
target_link_libraries(GameBackboneDemo GameBackbone)

# Include own header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/header)
