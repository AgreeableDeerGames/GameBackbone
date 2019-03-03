# CMakeLists for GameBackbone library

cmake_minimum_required (VERSION 3.8)

add_library(GameBackbone SHARED 
# include

  # core
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/AnimatedSprite.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/AnimationSet.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/BackboneBaseExceptions.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/CompoundSprite.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/CoreEventController.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/GameRegion.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/RelativeRotationSprite.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/Updatable.h"

  # navigation
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Navigation/CoordinateConverter.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Navigation/NavigationGridData.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Navigation/NavigationTools.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Navigation/PathFinder.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Navigation/PathRequest.h"

  # util
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/Array2D.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/Array3D.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/Cluster.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/ClusterGreenhouse.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/DebugIncludes.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/DllUtil.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/FileManager.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/FileReader.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/FileWriter.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/Point.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/RandGen.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/UtilMath.h"

# source

  # core
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/AnimatedSprite.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/AnimationSet.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/CompoundSprite.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/GameRegion.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/RelativeRotationSprite.cpp"

  # navigation
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Navigation/CoordinateConverter.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Navigation/NavigationTools.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Navigation/PathFinder.cpp"

  # Util
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Util/Cluster.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Util/ClusterGreenhouse.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Util/dllmain.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Util/FileManager.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Util/FileReader.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Util/FileWriter.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Util/RandGen.cpp"
)

set_target_properties(GameBackbone PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

find_package(SFML 2 COMPONENTS network audio graphics window system)
if(SFML_FOUND)
  target_link_libraries(GameBackbone PUBLIC sfml-graphics sfml-network sfml-audio sfml-window sfml-system)
endif()

find_package(TGUI 0.8.2 REQUIRED)
if(TGUI_FOUND)
  target_link_libraries(GameBackbone PUBLIC tgui)
endif()

target_include_directories(GameBackbone PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)

# configure and install
include("${CMAKE_SOURCE_DIR}/cmake/Utils/GBExportAndInstall.cmake")