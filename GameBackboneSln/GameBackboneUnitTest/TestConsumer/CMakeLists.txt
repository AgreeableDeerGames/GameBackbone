cmake_minimum_required(VERSION 3.8.0)
project(TestGameBackboneConsumer VERSION 1.0.0)

add_executable(TestGameBackboneConsumer main.cpp)

# GameBackbone has these as public targets. This means that they are automatically
# added to the target_link_libraries for TestGameBackboneConsumer
# TestGameBackboneConsumer still needs to find the packages for GB to link agains though.
find_package(SFML 2 COMPONENTS network audio graphics window system)
find_package(TGUI 0.8.2 REQUIRED)

find_package(GameBackbone 0.2.2 REQUIRED)
target_link_libraries(TestGameBackboneConsumer PRIVATE GameBackbone)


