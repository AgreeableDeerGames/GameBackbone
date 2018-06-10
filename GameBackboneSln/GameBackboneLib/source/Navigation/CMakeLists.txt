# CMakeLists for GameBackboneDll's Navigation source files
cmake_minimum_required (VERSION 3.8)

SET(LOCAL_SOURCE_FILES
  "CoordinateConverter.cpp"
  "NavigationTools.cpp"
  "PathFinder.cpp"
)

SET(FULL_PATH_LOCAL_FILES "")
PREPEND(FULL_PATH_LOCAL_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${LOCAL_SOURCE_FILES})
SET(SOURCE_FILES ${SOURCE_FILES} ${FULL_PATH_LOCAL_FILES} PARENT_SCOPE)