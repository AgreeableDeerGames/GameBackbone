# CMakeLists for GameBackboneUnitTest executable 

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
 "Source/InputHandlerTests.cpp")

# Set warnings to GB test defaults
gamebackbone_target_set_default_warnings_for_tests(GameBackboneUnitTest)

target_link_libraries(GameBackboneUnitTest PRIVATE GameBackbone)

find_package(Boost 1.68 COMPONENTS unit_test_framework REQUIRED)
if(Boost_FOUND)
	TARGET_include_directories(GameBackboneUnitTest PRIVATE ${Boost_INCLUDE_DIRS})
	target_link_libraries(GameBackboneUnitTest PRIVATE ${Boost_LIBRARIES})
endif()

# declares a test with all boost tests
add_test(NAME GBUnitTests COMMAND GameBackboneUnitTest WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
