# CMakeLists for GameBackbone library

include("${PROJECT_SOURCE_DIR}/cmake/Utils/GameBackboneCompilerOptions.cmake")

add_library(GameBackbone SHARED 
# include

  # core
  "Include/GameBackbone/Core/AnimatedSprite.h"
  "Include/GameBackbone/Core/AnimationSet.h"
  "Include/GameBackbone/Core/BasicGameRegion.h"
  "Include/GameBackbone/Core/CompoundSprite.h"
  "Include/GameBackbone/Core/CoreEventController.h"
  "Include/GameBackbone/Core/GameRegion.h"
  "Include/GameBackbone/Core/UniformAnimationSet.h"
  "Include/GameBackbone/Core/Updatable.h"

  # util
  "Include/GameBackbone/Util/DllUtil.h"
  "Include/GameBackbone/Util/RandGen.h"
  "Include/GameBackbone/Util/SFUtil.h"
  "Include/GameBackbone/Util/UtilMath.h"

  # user input
  "Include/GameBackbone/UserInput/InputHandler.h"

# source

  # core
  
  "Source/Core/AnimatedSprite.cpp"
  "Source/Core/AnimationSet.cpp"
  "Source/Core/BasicGameRegion.cpp"
  "Source/Core/CompoundSprite.cpp"
  "Source/Core/CoreEventController.cpp"
  "Source/Core/GameRegion.cpp"
  "Source/Core/UniformAnimationSet.cpp"

  # Util
  "Source/Util/RandGen.cpp"
)

set_target_properties(
  GameBackbone 
  PROPERTIES
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    VERSION ${GameBackboneProject_VERSION}
)

# Set warnings to GB defaults
gamebackbone_target_set_default_warnings(GameBackbone)

# Clang Tidy
option(GAMEBACKBONE_RUN_CLANG_TIDY "Run Clang Tidy when building GB" OFF)
if (GAMEBACKBONE_RUN_CLANG_TIDY)
# enable clang tidy
  include("${PROJECT_SOURCE_DIR}/cmake/Utils/GameBackboneClangTidy.cmake")
  gamebackbone_target_enable_clang_tidy(GameBackbone)
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

# Install
set(GAME_BACKBONE_INSTALL_TARGETS GameBackbone)
include(${PROJECT_SOURCE_DIR}/cmake/Utils/GBExportAndInstall.cmake)