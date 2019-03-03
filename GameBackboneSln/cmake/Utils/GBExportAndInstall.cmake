#Installs and exports GameBackbone

cmake_minimum_required (VERSION 3.8)

set(CMAKE_INSTALL_GENERATION_DIR "${CMAKE_BINARY_DIR}/CmakeExport")
set(EXPORT_TARGETS_GENERATION_PATH "${CMAKE_INSTALL_GENERATION_DIR}/GameBackboneSharedTargets.cmake")
set(GAMEBACKBONE_INSTALL_CMAKE_DIR "lib/cmake/GameBackbone")
set(GAMEBACKBONE_PUBLIC_INCLUDE_INSTALL_DIR include)

# configure config files
include(CMakePackageConfigHelpers)
# configure_package_config_file (
#     "${CMAKE_SOURCE_DIR}/cmake/Utils/GameBackboneConfig.cmake.in"
#     ${EXPORT_TARGETS_GENERATION_DIR}
#     INSTALL_DESTINATION ${GAMEBACKBONE_INSTALL_CMAKE_DIR}
#     PATH_VARS GAMEBACKBONE_INSTALL_CMAKE_DIR GAMEBACKBONE_PUBLIC_INCLUDE_INSTALL_DIR
# )

configure_package_config_file (
    "${CMAKE_SOURCE_DIR}/cmake/Utils/GameBackboneConfig.cmake.in"
    "${CMAKE_INSTALL_GENERATION_DIR}/GameBackboneConfig.cmake"
    INSTALL_DESTINATION ${GAMEBACKBONE_INSTALL_CMAKE_DIR}
    PATH_VARS GAMEBACKBONE_INSTALL_CMAKE_DIR GAMEBACKBONE_PUBLIC_INCLUDE_INSTALL_DIR
)

write_basic_package_version_file (
    "${CMAKE_INSTALL_GENERATION_DIR}/GameBackboneConfigVersion.cmake"
    VERSION ${CMAKE_VERSION}
    COMPATIBILITY ExactVersion # We can relax this after GB is more stable
)

# install GameBackbone lib
install(
    TARGETS GameBackbone
    EXPORT GameBackbonePublicTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

#install GameBackbone headers
install(
    DIRECTORY "${CMAKE_SOURCE_DIR}/GameBackbone/Include"
    DESTINATION ${GAMEBACKBONE_PUBLIC_INCLUDE_INSTALL_DIR}
)

# install Cmake Files
install (
    EXPORT GameBackbonePublicTargets
    DESTINATION ${GAMEBACKBONE_INSTALL_CMAKE_DIR}
)
install(
    DIRECTORY ${EXPORT_TARGETS_GENERATION_DIR}
    DESTINATION ${GAMEBACKBONE_INSTALL_CMAKE_DIR}
)