# CMakeLists for GameBackboneDll's backbone header files
cmake_minimum_required (VERSION 3.8)
SET(LOCAL_SOURCE_FILES
  "AnimatedSprite.h"
  "AnimationSet.h"
  "BackboneBaseExceptions.h"
  "CompoundSprite.h"
  "CoreEventController.h"
  "GameRegion.h"
  "RelativeRotationSprite.h"
  "Updatable.h"
)

SET(FULL_PATH_LOCAL_FILES "")
PREPEND(FULL_PATH_LOCAL_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${LOCAL_SOURCE_FILES})
SET(SOURCE_FILES ${SOURCE_FILES} ${FULL_PATH_LOCAL_FILES} PARENT_SCOPE)