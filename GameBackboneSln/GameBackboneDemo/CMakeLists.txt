# CMakeLists for GameBackbone demo executable 

cmake_minimum_required (VERSION 3.8)

include("../cmake/Utils/GameBackboneMessage.cmake")

add_executable(GameBackboneDemo
# headers
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/DemoCoreEventController.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/DemoRegion.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/MainMenuDemoRegion.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/NavigationDemoRegion.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/PlatformDemoRegion.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/RegionChangeDemoRegion.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/ScaleAndRotationDemoRegion.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/GameBackboneDemo/targetver.h"

# source
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/DemoCoreEventController.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/DemoRegion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/MainMenuDemoRegion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/NavigationDemoRegion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/PlatformDemoRegion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/RegionChangeDemoRegion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/ScaleAndRotationDemoRegion.cpp"
)

# Link Box
# Allow users to use VCPKG and its unofficial version of Box2D if they want
# Otherwise find Box2D with custom FindBOX2D
option(USE_VCPKG_BOX2D "Using VCPKG to get Box2D" OFF)
if(${USE_VCPKG_BOX2D})
	gamebackbone_message("Using Box2D from vcpkg.")
    find_package(unofficial-box2d CONFIG REQUIRED)
    target_link_libraries(GameBackboneDemo PRIVATE unofficial::box2d::Box2D)
else()
	gamebackbone_message("Using custom find module for Box2D. To use vcpkg provided Box2D set USE_VCPKG_BOX2D to ON")
    find_package(BOX2D REQUIRED)
    target_link_libraries(GameBackboneDemo PRIVATE ${BOX2D_LIBRARY})
    include_directories(${BOX2D_INCLUDE_DIR})
endif()

# This is how to link to GB if it was being built from a different CMake process
# find_package(GameBackbone REQUIRED) 
# if(GB_FOUND) 
#   include_directories(${GB_INCLUDE_DIR}) 
#   target_link_libraries(GameBackboneDemo ${GB_LIBRARY}) 
# endif() 

# link to GB
target_link_libraries(GameBackboneDemo PRIVATE GameBackbone)

# Include own header files
target_include_directories(GameBackboneDemo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Include)
