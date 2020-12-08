# Installing GameBackbone

This guide will show you how to 

- [Installing GameBackbone](#installing-gamebackbone)
  - [1: vcpkg](#1-vcpkg)
  - [2: Custom Build and Install](#2-custom-build-and-install)
    - [2.1: Required Software](#21-required-software)
    - [2.2: Install dependencies](#22-install-dependencies)
      - [2.2.1: vcpkg install](#221-vcpkg-install)
      - [2.2.2: custom install](#222-custom-install)
    - [2.3: Install GameBackbone](#23-install-gamebackbone)

## 1: vcpkg
1. Follow the quickstart guide for your platform
   * [Windows](https://github.com/AgreeableDeerGames/ag_vcpkg#quick-start-windows)
   * [Unix](https://github.com/AgreeableDeerGames/ag_vcpkg#quick-start-windows)
2. install GameBackbone
   * `vcpkg install gamebackbone:[vcpkg-triplet-here]`

## 2: Custom Build and Install

### 2.1: Required Software
* [Download](https://cmake.org/download/) CMake 3.8 or newer
* Supported c++ compiler
  * MSVC 14.25
  * GCC 7.3
  * Other C++ 17 compliant compilers should work, but are untested 

### 2.2: Install dependencies
#### 2.2.1: vcpkg install
1. Follow the quickstart guide for your platform
   * [Windows](https://github.com/AgreeableDeerGames/ag_vcpkg#quick-start-windows)
   * [Unix](https://github.com/AgreeableDeerGames/ag_vcpkg#quick-start-windows)
2. install sfml
   * `vcpkg install sfml:[vcpkg-triplet-here]`
3. install tgui (required for demo only)
   * `vcpkg install tgui:[vcpkg-triplet-here]`
4. install box2d (required for demo only)
   * `vcpkg install box2d:[vcpkg-triplet-here]`
5. install boost (required for tests only)
   * `vcpkg install boost:[vcpkg-triplet-here]`

#### 2.2.2: custom install
Build and install the following dependencies on your own. 
* [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/)
* [Box2D](https://box2d.org/) (required for demo only)
* [TGUI](https://tgui.eu/) (required for demo only)
* [Boost](https://www.boost.org/users/download/) (required for tests only)

### 2.3: Install GameBackbone

1. Run cmake with your desired options. Be sure to tell cmake where to find GameBackbone's dependencies. 
2. Run make install (or equivalent)

Sample invocation using custom install of dependencies (run from the root folder of the project):

    mkdir build
    cd build
    cmake .. -DBOOST_ROOT=/path/to/boost/install -DSFML_DIR=/path/to/sfml/lib/cmake/SFML -DTGUI_DIR=/path/to/tgui/lib/cmake/TGUI -DBOX2D_DIR=/path/to/box2d/install -DCMAKE_INSTALL_PREFIX=/GameBackbone/Install/Dir/

    make install

Sample invocation using vcpkg install of dependencies (run from the root folder of the project):

    mkdir build
    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_INSTALL_PREFIX=/GameBackbone/Install/Dir

    cmake --build . --target Install

In the above examples simply set GAMEBACKBONE_BUILD_TESTS or GAMEBACKBONE_BUILD_DEMO to 'ON' to enable building the tests or the demo respectively. These options are OFF by default.