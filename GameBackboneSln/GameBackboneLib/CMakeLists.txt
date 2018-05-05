# CMakeLists for GameBackbone library

cmake_minimum_required (VERSION 3.8)

set(SOURCE_FILES "")

add_subdirectory("source")
add_subdirectory("header")

message("SOURCE_FILES: " ${SOURCE_FILES})

add_library(GameBackbone SHARED ${SOURCE_FILES})
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(GameBackbone ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

find_package(TGUI REQUIRED)
if(TGUI_FOUND)
  include_directories(${TGUI_INCLUDE_DIR})
  target_link_libraries(GameBackbone ${TGUI_LIBRARY}})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/header)
