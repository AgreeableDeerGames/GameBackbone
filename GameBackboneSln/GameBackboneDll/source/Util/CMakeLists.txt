# CMakeLists for GameBackboneDll's Util source files
cmake_minimum_required (VERSION 3.8)

SET(LOCAL_SOURCE_FILES
  Cluster.cpp
  ClusterGreenhouse.cpp
  dllmain.cpp
  FileManager.cpp
  FileReader.cpp
  FileWriter.cpp
  RandGen.cpp
)

PREPEND(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${LOCAL_SOURCE_FILES})
SET(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)