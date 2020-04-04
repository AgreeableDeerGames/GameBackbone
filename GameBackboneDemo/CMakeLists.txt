# CMakeLists for GameBackbone demo executable 

cmake_minimum_required (VERSION 3.8)

include("${CMAKE_SOURCE_DIR}/cmake/Utils/GameBackboneMessage.cmake")


add_executable(GameBackboneDemo
# headers
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/AnimationDemoRegion.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/DemoCoreEventController.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/DemoRegion.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/MainMenuDemoRegion.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/PlatformDemoRegion.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/RegionChangeDemoRegion.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/ScaleAndRotationDemoRegion.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/targetver.h"

# source
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/AnimationDemoRegion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/DemoCoreEventController.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/DemoRegion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/MainMenuDemoRegion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/PlatformDemoRegion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/RegionChangeDemoRegion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/ScaleAndRotationDemoRegion.cpp"
)

# Set warnings to GB defaults
gamebackbone_target_set_default_warnings(GameBackboneDemo)

option(GAMEBACKBONE_BUILD_PLATFORM_DEMO "Include the platform Demo in the GB Demo executable (Requires Box2D)" ON)
if (${GAMEBACKBONE_BUILD_PLATFORM_DEMO})
    # Warn user about Box2D
    gamebackbone_message("Building demo with PlatformDemo. This requires Box2D.")
    gamebackbone_message("Set GAMEBACKBONE_BUILD_PLATFORM_DEMO to 'OFF' to disable PlatformDemo.")

    # Link Box
    # Allow users to use vcpkg and its unofficial version of Box2D if they want
    # Otherwise find Box2D with custom FindBOX2D
    option(USE_VCPKG_BOX2D "Using vcpkg to get Box2D" OFF)
    if(${USE_VCPKG_BOX2D})
        gamebackbone_message("Using Box2D from vcpkg.")
        find_package(unofficial-box2d CONFIG REQUIRED)
        target_link_libraries(GameBackboneDemo PRIVATE unofficial::box2d::Box2D)
    else()
        gamebackbone_message("Using custom find module for Box2D. If you want to use the unofficial Box2D package on vcpkg, set USE_VCPKG_BOX2D to ON.")
        find_package(BOX2D REQUIRED)
        target_link_libraries(GameBackboneDemo PRIVATE ${BOX2D_LIBRARY})
        include_directories(${BOX2D_INCLUDE_DIR})
    endif()

    # Define macro to prevent PlatformDemo from Compiling
    # This macro shares the name of the cmake toggle but is a C++ macro
    target_compile_definitions(GameBackboneDemo PRIVATE "GAMEBACKBONE_BUILD_PLATFORM_DEMO")
else()
    gamebackbone_message("Building demo without PlatformDemo")
endif()

find_package(TGUI 0.8.2 REQUIRED)
if(TGUI_FOUND)
  target_link_libraries(GameBackboneDemo PUBLIC tgui)
endif()

# Link to GB
target_link_libraries(GameBackboneDemo PRIVATE GameBackbone)

# Include own header files
target_include_directories(GameBackboneDemo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Include)
