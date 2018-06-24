# CMakeLists for GameBackboneUnitTest executable 

cmake_minimum_required (VERSION 3.8)
enable_testing()

set(SOURCE_FILES "")

add_subdirectory("source")

add_executable(GameBackboneUnitTest ${SOURCE_FILES})

# link to SFML and TGUI
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(GameBackboneUnitTest ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

find_package(TGUI REQUIRED)
if(TGUI_FOUND)
  include_directories(${TGUI_INCLUDE_DIR})
  target_link_libraries(GameBackboneUnitTest ${TGUI_LIBRARY})
endif()

find_package(GameBackbone REQUIRED)
if(GB_FOUND)
  include_directories(${GB_INCLUDE_DIR})
  target_link_libraries(GameBackboneUnitTest ${GB_LIBRARY})
endif()

set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost 1.67 COMPONENTS unit_test_framework test_exec_monitor REQUIRED)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(GameBackboneUnitTest ${Boost_LIBRARIES})
endif()

# declares a test with our executable
add_test(NAME test1 COMMAND GameBackboneUnitTest)