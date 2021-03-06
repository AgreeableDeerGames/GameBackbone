# CMakeLists for GameBackbone demo executable 

include("${PROJECT_SOURCE_DIR}/cmake/Utils/GameBackboneMessage.cmake")


add_executable(GameBackboneDemo
# headers
    "Include/GameBackboneDemo/AnimationDemoRegion.h"
    "Include/GameBackboneDemo/DemoCoreEventController.h"
    "Include/GameBackboneDemo/DemoRegion.h"
    "Include/GameBackboneDemo/MainMenuDemoRegion.h"
    "Include/GameBackboneDemo/PlatformDemoRegion.h"
    "Include/GameBackboneDemo/RegionChangeDemoRegion.h"
    "Include/GameBackboneDemo/ScaleAndRotationDemoRegion.h"
    "Include/GameBackboneDemo/targetver.h"

# source
    "Source/AnimationDemoRegion.cpp"
    "Source/DemoCoreEventController.cpp"
    "Source/DemoRegion.cpp"
    "Source/main.cpp"
    "Source/MainMenuDemoRegion.cpp"
    "Source/PlatformDemoRegion.cpp"
    "Source/RegionChangeDemoRegion.cpp"
    "Source/ScaleAndRotationDemoRegion.cpp"
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
target_link_libraries(GameBackboneDemo PUBLIC tgui)

# Link to GB
target_link_libraries(GameBackboneDemo PRIVATE GameBackbone)

# Include own header files
target_include_directories(GameBackboneDemo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Include)
