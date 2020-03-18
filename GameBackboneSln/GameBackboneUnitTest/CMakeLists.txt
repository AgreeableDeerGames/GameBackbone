# CMakeLists for GameBackboneUnitTest executable 

cmake_minimum_required (VERSION 3.8)

add_executable(GameBackboneUnitTest 
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/stdafx.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/stdafx.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/AnimatedSpriteTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/AnimationSetTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/Array2DTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/BasicGameRegionTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/ClusterGreenhouseTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/ClusterTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/CompoundSpriteTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/CoordinateConverterTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/CoreEventControllerTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/FileManagerTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/FileReaderTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/FileWriterTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/GameRegionTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/NavigationToolsTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/PathFinderTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/RandGenTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/targetver.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/UniformAnimationSetTests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/UtilMathTests.cpp"
)

# Set warnings to GB test defaults
gamebackbone_target_set_default_warnings_for_tests(GameBackboneUnitTest)

target_link_libraries(GameBackboneUnitTest PRIVATE GameBackbone)

find_package(Boost 1.65 COMPONENTS unit_test_framework REQUIRED)
if(Boost_FOUND)
	TARGET_include_directories(GameBackboneUnitTest PRIVATE ${Boost_INCLUDE_DIRS})
	target_link_libraries(GameBackboneUnitTest PRIVATE ${Boost_LIBRARIES})
endif()

# declares a test with all boost tests
add_test(NAME AnimatedSpriteTests COMMAND GameBackboneUnitTest --run_test=AnimatedSpriteTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME AnimationSetTests COMMAND GameBackboneUnitTest --run_test=AnimationSetTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME Array2DTests COMMAND GameBackboneUnitTest --run_test=Array2D_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME BasicGameRegionTests COMMAND GameBackboneUnitTest --run_test=BasicGameRegionTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME ClusterGreenhouseTests COMMAND GameBackboneUnitTest --run_test=ClusterGreenhouse_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME ClusterTests COMMAND GameBackboneUnitTest --run_test=Cluster_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME CompoundSpriteTests COMMAND GameBackboneUnitTest --run_test=CompoundSpriteTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME CoordinateConverterTests COMMAND GameBackboneUnitTest --run_test=CoordinateConverter_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME CoreEventControllerTests COMMAND GameBackboneUnitTest --run_test=CoreEventControllerTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME FileManagerTests COMMAND GameBackboneUnitTest --run_test=FileManager_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME FileReaderTests COMMAND GameBackboneUnitTest --run_test=FileReader_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME FileWriterTests COMMAND GameBackboneUnitTest --run_test=FileWriter_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME GameRegionTests COMMAND GameBackboneUnitTest --run_test=GameRegion_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME NavigationToolsTests COMMAND GameBackboneUnitTest --run_test=NavigationToolsTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME PathFinderTests COMMAND GameBackboneUnitTest --run_test=Pathfinder_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME RandGenTests COMMAND GameBackboneUnitTest --run_test=RandGen_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME UtilMathTests COMMAND GameBackboneUnitTest --run_test=UtilMathTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

