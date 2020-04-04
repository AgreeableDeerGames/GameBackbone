# CMakeLists for GameBackbone library

cmake_minimum_required (VERSION 3.8)

include("${GAMEBACKBONE_TOP_FOLDER}/cmake/Utils/GameBackboneCompilerOptions.cmake")

add_library(GameBackbone SHARED 
# include

  # core
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/Animation.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/AnimatedSprite.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/AnimationSet.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/BackboneBaseExceptions.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/BasicGameRegion.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/CompoundSprite.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/CoreEventController.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/GameRegion.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/UniformAnimationSet.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Core/Updatable.h"

  # util
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/DebugIncludes.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/DllUtil.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/RandGen.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/SFUtil.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackbone/Util/UtilMath.h"

# source

  # core
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Animation.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/AnimatedSprite.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/AnimationSet.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/BasicGameRegion.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/CompoundSprite.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/CoreEventController.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/GameRegion.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/UniformAnimationSet.cpp"

  # Util
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Util/dllmain.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Util/RandGen.cpp"
)

set_target_properties(
  GameBackbone 
  PROPERTIES
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    VERSION 0.3.0
)

# Set warnings to GB defaults
gamebackbone_target_set_default_warnings(GameBackbone)

# Clang Tidy
option(GAMEBACKBONE_RUN_CLANG_TIDY "Run Clang Tidy when building GB" OFF)
if (GAMEBACKBONE_RUN_CLANG_TIDY)
  # enable clang tidy
  include("${CMAKE_SOURCE_DIR}/cmake/Utils/GameBackboneClangTidy.cmake")
  if(CLANG_TIDY_EXE)
    gamebackbone_message("Clang-Tidy enabled. Clang-Tidy will be run on build.")
    set_target_properties (
      GameBackbone PROPERTIES
      CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
    )
  # Clang Tidy on, but not found
  else()
    gamebackbone_warning("Clang Tidy enabled but not found!")
  endif()
else()
  gamebackbone_message("Clang Tidy off. Set GAMEBACKBONE_RUN_CLANG_TIDY to 'ON' to use Clang Tidy.")
endif()

find_package(SFML 2 COMPONENTS network audio graphics window system REQUIRED)
if(SFML_FOUND)
  target_link_libraries(GameBackbone PUBLIC sfml-graphics sfml-network sfml-audio sfml-window sfml-system)
endif()

target_include_directories(
  GameBackbone
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
      $<INSTALL_INTERFACE:include>
)

# configure and install
include("${CMAKE_SOURCE_DIR}/cmake/Utils/GBExportAndInstall.cmake")