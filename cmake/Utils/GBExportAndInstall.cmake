#Installs and exports GameBackbone

set(CMAKE_INSTALL_GENERATION_DIR "${CMAKE_BINARY_DIR}/CmakeExport")
set(GAMEBACKBONE_INSTALL_CMAKE_DIR "lib/cmake/GameBackbone")
set(GAMEBACKBONE_PUBLIC_INCLUDE_INSTALL_DIR include)

# configure config files
include(CMakePackageConfigHelpers)
get_target_property(GAMEBACKBONE_TARGET_VERSION GameBackbone VERSION)
configure_package_config_file (
    "${PROJECT_SOURCE_DIR}/cmake/Utils/GameBackboneConfig.cmake.in"
    "${CMAKE_INSTALL_GENERATION_DIR}/GameBackboneConfig.cmake"
    INSTALL_DESTINATION ${GAMEBACKBONE_INSTALL_CMAKE_DIR}
    PATH_VARS GAMEBACKBONE_INSTALL_CMAKE_DIR GAMEBACKBONE_PUBLIC_INCLUDE_INSTALL_DIR
)

write_basic_package_version_file (
    "${CMAKE_INSTALL_GENERATION_DIR}/GameBackboneConfigVersion.cmake"
    VERSION ${GAMEBACKBONE_TARGET_VERSION}
    COMPATIBILITY ExactVersion # We can relax this after GB is more stable
)

# install GameBackbone lib
install(
    TARGETS ${GAME_BACKBONE_INSTALL_TARGETS}
    EXPORT GameBackbonePublicTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

#install GameBackbone headers
install(
    DIRECTORY "${CMAKE_SOURCE_DIR}/GameBackbone/Include/GameBackbone"
    DESTINATION ${GAMEBACKBONE_PUBLIC_INCLUDE_INSTALL_DIR}
)

# install CMake Files
install (
    EXPORT GameBackbonePublicTargets
    DESTINATION ${GAMEBACKBONE_INSTALL_CMAKE_DIR}
)
install(
    FILES
        ${CMAKE_INSTALL_GENERATION_DIR}/GameBackboneConfig.cmake
        ${CMAKE_INSTALL_GENERATION_DIR}/GameBackboneConfigVersion.cmake
    DESTINATION
        ${GAMEBACKBONE_INSTALL_CMAKE_DIR}
)