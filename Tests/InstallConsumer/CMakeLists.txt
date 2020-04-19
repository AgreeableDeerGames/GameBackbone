cmake_minimum_required(VERSION 3.8.0)
project(GameBackboneInstallConsumer VERSION 1.0.0)

add_executable(GameBackboneInstallConsumer main.cpp)

# GameBackbone has these as public targets. This means that they are automatically
# added to the target_link_libraries for GameBackboneInstallConsumer
# GameBackboneInstallConsumer still needs to find the packages for GB to link agains though.
find_package(SFML 2 COMPONENTS network audio graphics window system REQUIRED)

find_package(GameBackbone 0.4.0 REQUIRED)
target_link_libraries(GameBackboneInstallConsumer PRIVATE GameBackbone)


