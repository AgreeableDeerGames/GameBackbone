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

#find_package(Boost COMPONENTS unit_test_framework REQUIRED)
#if(Boost_FOUND)
#	include_directories(${Boost_INCLUDE_DIRS})
#	message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
#	message($ENV{BOOST_ROOT})
#	message("BOOST INCLUDE DIRS: " ${Boost_INCLUDE_DIRS})
#	message("BOOST libs : " ${Boost_LIBRARIES})
#	message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
#	target_link_libraries(GameBackboneUnitTest ${Boost_LIBRARIES})
#endif()

include_directories("E:/Programing/Programing/Cpp/Boost/boost_1_67_0_x64")
target_link_libraries(GameBackboneUnitTest "E:/Programing/Programing/Cpp/Boost/boost_1_67_0_x64/lib64-msvc-14.1/libboost_unit_test_framework-vc141-mt-gd-x64-1_67.lib" 
											"E:/Programing/Programing/Cpp/Boost/boost_1_67_0_x64/lib64-msvc-14.1/libboost_test_exec_monitor-vc141-mt-gd-x64-1_67.lib")
#target_link_libraries(GameBackboneUnitTest ${BOOST_LIB})


# link to GB
target_include_directories(GameBackboneUnitTest PRIVATE ${GAMEBACKBONE_TOP_FOLDER}/GameBackboneLib/header)
target_link_libraries(GameBackboneUnitTest ${GAMEBACKBONE_TOP_FOLDER}/build/lib/GameBackbone.lib)

# declares a test with our executable
add_test(NAME test1 COMMAND GameBackboneUnitTest)