# CMakeLists for GameBackboneDemo's header files
cmake_minimum_required (VERSION 3.8)
SET(LOCAL_SOURCE_FILES
  "DemoCoreEventController.h"
  "DemoRegion.h"
  "MainMenuDemoRegion.h"
  "NavigationDemoRegion.h"
  "RegionChangeDemoRegion.h"
  "ScaleAndRotationDemoRegion.h"
  "targetver.h"
)

SET(FULL_PATH_LOCAL_FILES "")
PREPEND(FULL_PATH_LOCAL_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${LOCAL_SOURCE_FILES})
SET(SOURCE_FILES ${SOURCE_FILES} ${FULL_PATH_LOCAL_FILES} PARENT_SCOPE)