# CMakeLists for GameBackboneUnitTest executable 

cmake_minimum_required (VERSION 3.8)

enable_testing()

set(SOURCE_FILES "")

add_subdirectory("source")

add_executable(GameBackboneUnitTest ${SOURCE_FILES})

# link to SFML and TGUI
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  target_link_libraries(GameBackboneUnitTest sfml-graphics sfml-network sfml-audio sfml-window sfml-system)
endif()

find_package(TGUI REQUIRED)
if(TGUI_FOUND)
  target_link_libraries(GameBackboneUnitTest tgui)
endif()

include_directories(${GB_INCLUDE_DIR})
target_link_libraries(GameBackboneUnitTest GameBackbone)

find_package(Boost 1.68 COMPONENTS unit_test_framework REQUIRED)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(GameBackboneUnitTest ${Boost_LIBRARIES})
endif()

# declares a test with all boost tests
add_test(NAME AnimatedSpriteTests COMMAND GameBackboneUnitTest --run_test=AnimatedSpriteTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME AnimationSetTests COMMAND GameBackboneUnitTest --run_test=AnimationSet_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME Array2DTests COMMAND GameBackboneUnitTest --run_test=Array2D_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME Array3DTests COMMAND GameBackboneUnitTest --run_test=Array3D_Tests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
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
add_test(NAME RelativeRotationSpriteTests COMMAND GameBackboneUnitTest --run_test=RelativeRotionSpriteTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_test(NAME UtilMathTests COMMAND GameBackboneUnitTest --run_test=UtilMathTests WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

