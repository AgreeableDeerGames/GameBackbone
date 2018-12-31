# CMakeLists for GameBackbone library

cmake_minimum_required (VERSION 3.8)

set(SOURCE_FILES "")

add_subdirectory("source")
add_subdirectory("header")

add_library(GameBackbone SHARED ${SOURCE_FILES})
set_target_properties(GameBackbone PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
find_package(SFML 2 COMPONENTS network audio graphics window system)
if(SFML_FOUND)
  target_link_libraries(GameBackbone sfml-graphics sfml-network sfml-audio sfml-window sfml-system)
endif()

find_package(TGUI 0.8.2 REQUIRED)
if(TGUI_FOUND)
  target_link_libraries(GameBackbone tgui)
endif()

target_include_directories(GameBackbone PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header)

