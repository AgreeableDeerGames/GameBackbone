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
1. Clone ag_vcpkg (a fork of vcpkg with a GameBackbone package)
2. Follow the standard vcpkg setup
3. Run vcpkg install gamebackbone 

## 2: Custom Build and Install

### 2.1: Required Software
* [Download](https://cmake.org/download/) CMake 3.8 or newer
* Supported c++ compiler
  * MSVC 14.1
  * [Clang 7](http://releases.llvm.org/download.html)
  * GCC 7.3

### 2.2: Install dependencies
#### 2.2.1: vcpkg install

You can either install all the dependencies on your own or use the installVCPKG script to install them for you.

*  Using installVCPKG.py
   * Run installVCPKG.py from the Scripts folder
     * Run with -h for help
* Manual install
  * vcpkg install sfml
  * vcpkg install tgui
  * vcpkg install boost (optional)
  * vcpkg install box2d (optional)

#### 2.2.2: custom install
Build and install the following dependencies on your own. 
* [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/)
* [TGUI](https://tgui.eu/)
* [Box2D](https://box2d.org/) (optional for demo)
* [Boost](https://www.boost.org/users/download/) (optional for tests)

### 2.3: Install GameBackbone

1. Run cmake with your desired options. Be sure to tell cmake where to find GameBackbone's dependencies. 
2. Run make install (or equivalent)

Sample invocation using custom install of dependencies (from GameBackboneSln/build):

    cmake .. -DBOOST_ROOT=/path/to/boost/install -DSFML_DIR=/path/to/sfml/lib/cmake/SFML -DTGUI_DIR=/path/to/tgui/lib/cmake/TGUI -DBOX2D_DIR=/path/to/box2d/install -DCMAKE_INSTALL_PREFIX=/GameBackbone/Install/Dir/

    make install

Sample invocation using vcpkg install of dependencies (from GameBackboneSln/build):

    cmake .. -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_INSTALL_PREFIX=/GameBackbone/Install/Dir

    make install

In the above examples simply set GAMEBACKBONE_BUILD_TESTS or GAMEBACKBONE_BUILD_DEMO to 'ON' to enable building the tests or the demo respectively. These options are OFF by default.