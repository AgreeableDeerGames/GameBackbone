# CMakeLists for GameBackboneUnitTests source files
cmake_minimum_required (VERSION 3.8)
SET(LOCAL_SOURCE_FILES
	"stdafx.h"
	"stdafx.cpp"
	"AnimatedSpriteTests.cpp"
	"AnimationSetTests.cpp"
	"Array2DTests.cpp"
	"Array3DTests.cpp"
	"ClusterGreenhouseTests.cpp"
	"ClusterTests.cpp"
	"CompoundSpriteTests.cpp"
	"CoordinateConverterTests.cpp"
	"CoreEventControllerTests.cpp"
	"FileManagerTests.cpp"
	"FileReaderTests.cpp"
	"FileWriterTests.cpp"
	"GameRegionTests.cpp"
	"NavigationToolsTests.cpp"
	"PathFinderTests.cpp"
	"RandGenTests.cpp"
	"RelativeRotationSpriteTests.cpp"
	"targetver.h"
	"UtilMathTests.cpp"
)

SET(FULL_PATH_LOCAL_FILES "")
PREPEND(FULL_PATH_LOCAL_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${LOCAL_SOURCE_FILES})
SET(SOURCE_FILES ${SOURCE_FILES} ${FULL_PATH_LOCAL_FILES} PARENT_SCOPE)

