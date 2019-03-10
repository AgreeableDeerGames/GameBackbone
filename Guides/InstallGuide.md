# Installing GameBackbone

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
2. follow the standard vcpkg setup
3. run vcpkg install gamebackbone 

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

*  installVCPKG.py
   * Run installVCPKG.py from the Scripts folder
     * run with -h for help
* manual install
  * vcpkg install sfml
  * vcpkg install tgui
  * vcpkg install box2d (optional)
  * vcpkg install box2d (optional)

#### 2.2.2: custom install
Build and install the following dependencies on your own. 
* [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/)
* [TGUI](https://tgui.eu/)
* [Box2D](https://box2d.org/) (optional for demo)
* [Boost](https://www.boost.org/users/download/) (optional for tests)

### 2.3: Install GameBackbone

1. Run cmake with your desired options. Be sure to tell cmake where to find GameBackbone's dependencies. 
2. run make install (or equivalent)

Sample invocation using custom install of dependencies (from GameBackboneSln/build)

    cmake .. -DBOOST_ROOT=/path/to/boost DSFML_DIR=/path/to/sfml -DTGUI_DIR=/path/to/tgui -DBOX2D_DIR=/path/to/box2d -DCMAKE_INSTALL_PREFIX=/GameBackbone/Install/Dir/ -DGAMEBACKBONE_BUILD_TESTS=ON -DGAMEBACKBONE_BUILD_DEMO=ON

    make install

Sample invocation using vcpkg install of dependencies (from GameBackboneSln/build)

    cmake .. -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_INSTALL_PREFIX=/GameBackbone/Install/Dir/ -DGAMEBACKBONE_BUILD_TESTS=ON -DGAMEBACKBONE_BUILD_DEMO=ON

    make install

In the above examples simply set GAMEBACKBONE_BUILD_TESTS or GAMEBACKBONE_BUILD_DEMO to 'OFF' to disable building the tests or the demo respectively.