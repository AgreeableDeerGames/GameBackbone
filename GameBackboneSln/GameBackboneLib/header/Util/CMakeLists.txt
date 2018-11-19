# CMakeLists for GameBackboneDll Util Headers

cmake_minimum_required (VERSION 3.8)
SET(LOCAL_SOURCE_FILES
	"Array2D.h"
	"Array3D.h"
	"Cluster.h"
	"ClusterGreenhouse.h"
	"DebugIncludes.h"
	"DllUtil.h"
	"FileManager.h"
	"FileReader.h"
	"FileWriter.h"
	"Point.h"
	"RandGen.h"
	"targetver.h"
	"UtilMath.h"
)

SET(FULL_PATH_LOCAL_FILES "")
PREPEND(FULL_PATH_LOCAL_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${LOCAL_SOURCE_FILES})
SET(SOURCE_FILES ${SOURCE_FILES} ${FULL_PATH_LOCAL_FILES} PARENT_SCOPE)