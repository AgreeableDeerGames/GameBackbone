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
  target_link_libraries(GameBackboneDemo ${TGUI_LIBRARY}})
endif()

# link to GB
include_directories(${GAMEBACKBONE_TOP_FOLDER}/GameBackboneLib/header)
target_link_libraries(GameBackboneDemo ${GAMEBACKBONE_TOP_FOLDER}/build/lib/GameBackbone.lib)

# Include own header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/header)
