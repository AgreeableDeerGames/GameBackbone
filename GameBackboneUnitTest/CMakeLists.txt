# CMakeLists for GameBackboneUnitTest executable 

cmake_minimum_required (VERSION 3.8)

add_executable(GameBackboneUnitTest 
	"Source/stdafx.h"
	"Source/stdafx.cpp"
	"Source/AnimatedSpriteTests.cpp"
	"Source/AnimationSetTests.cpp"
	"Source/BasicGameRegionTests.cpp"
	"Source/CompoundSpriteTests.cpp"
	"Source/CoreEventControllerTests.cpp"
	"Source/GameRegionTests.cpp"
	"Source/RandGenTests.cpp"
	"Source/SFUtilTests.cpp"
	"Source/targetver.h"
	"Source/UniformAnimationSetTests.cpp"
	"Source/UtilMathTests.cpp"
)

# Set warnings to GB test defaults
gamebackbone_target_set_default_warnings_for_tests(GameBackboneUnitTest)

target_link_libraries(GameBackboneUnitTest PRIVATE GameBackbone)

find_package(Boost 1.68 COMPONENTS unit_test_framework REQUIRED)
if(Boost_FOUND)
	TARGET_include_directories(GameBackboneUnitTest PRIVATE ${Boost_INCLUDE_DIRS})
	target_link_libraries(GameBackboneUnitTest PRIVATE ${Boost_LIBRARIES})
endif()

# declares a test with all boost tests
add_test(NAME AnimatedSpriteTests COMMAND GameBackboneUnitTest --run_test=AnimatedSpriteTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME AnimationSetTests COMMAND GameBackboneUnitTest --run_test=AnimationSetTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME BasicGameRegionTests COMMAND GameBackboneUnitTest --run_test=BasicGameRegionTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME CompoundSpriteTests COMMAND GameBackboneUnitTest --run_test=CompoundSpriteTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME CoreEventControllerTests COMMAND GameBackboneUnitTest --run_test=CoreEventControllerTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME GameRegionTests COMMAND GameBackboneUnitTest --run_test=GameRegion_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME RandGenTests COMMAND GameBackboneUnitTest --run_test=RandGen_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME UtilMathTests COMMAND GameBackboneUnitTest --run_test=UtilMathTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

