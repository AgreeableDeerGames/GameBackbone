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
  target_link_libraries(GameBackboneDemo ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

find_package(TGUI REQUIRED)
if(TGUI_FOUND)
  include_directories(${TGUI_INCLUDE_DIR})
  target_link_libraries(GameBackboneDemo ${TGUI_LIBRARY})
endif()

find_package(GameBackbone REQUIRED)
if(GB_FOUND)
  include_directories(${GB_INCLUDE_DIR})
  target_link_libraries(GameBackboneDemo ${GB_LIBRARY})
endif()

# Include own header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/header)
