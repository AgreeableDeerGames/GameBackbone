# CMakeLists for GameBackbone library

cmake_minimum_required (VERSION 3.8)

include("${PROJECT_SOURCE_DIR}/cmake/Utils/GameBackboneCompilerOptions.cmake")

add_library(GameBackbone SHARED 
# include

  # core
  "Include/GameBackbone/Core/Animation.h"
  "Include/GameBackbone/Core/AnimatedSprite.h"
  "Include/GameBackbone/Core/AnimationSet.h"
  "Include/GameBackbone/Core/BackboneBaseExceptions.h"
  "Include/GameBackbone/Core/BasicGameRegion.h"
  "Include/GameBackbone/Core/CompoundSprite.h"
  "Include/GameBackbone/Core/CoreEventController.h"
  "Include/GameBackbone/Core/GameRegion.h"
  "Include/GameBackbone/Core/UniformAnimationSet.h"
  "Include/GameBackbone/Core/Updatable.h"

  # util
  "Include/GameBackbone/Util/DebugIncludes.h"
  "Include/GameBackbone/Util/DllUtil.h"
  "Include/GameBackbone/Util/RandGen.h"
  "Include/GameBackbone/Util/SFUtil.h"
  "Include/GameBackbone/Util/UtilMath.h"

# source

  # core
  "Source/Core/Animation.cpp"
  "Source/Core/AnimatedSprite.cpp"
  "Source/Core/AnimationSet.cpp"
  "Source/Core/BasicGameRegion.cpp"
  "Source/Core/CompoundSprite.cpp"
  "Source/Core/CoreEventController.cpp"
  "Source/Core/GameRegion.cpp"
  "Source/Core/UniformAnimationSet.cpp"

  # Util
  "Source/Util/dllmain.cpp"
  "Source/Util/RandGen.cpp"
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
  include("${PROJECT_SOURCE_DIR}/cmake/Utils/GameBackboneClangTidy.cmake")
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