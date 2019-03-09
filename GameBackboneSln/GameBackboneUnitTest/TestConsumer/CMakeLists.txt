cmake_minimum_required(VERSION 3.8.0)
project(TestGameBackboneConsumer VERSION 1.0.0)

add_executable(TestGameBackboneConsumer main.cpp)

find_package(GameBackbone 0.1.2 REQUIRED)
target_link_libraries(TestGameBackboneConsumer PRIVATE GameBackbone)


