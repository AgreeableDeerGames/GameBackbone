# Installing GameBackbone

## vcpkg

## Custom Build and Install

### Required Software
* [Download](https://cmake.org/download/) CMake 3.8 or newer
* Supported c++ compiler
  * MSVC 14.1
  * [Clang 7](http://releases.llvm.org/download.html)
  * GCC 7.3

### install dependencies
#### vcpkg
##### installVCPKG.py
* Run installVCPKG.py from the Scripts folder
  * run -h for help
##### manual install
 * vcpkg install sfml
 * vcpkg install tgui
 * vcpkg install box2d (optional)
 * vcpkg install box2d (optional)

#### custom install
* [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/)
* [TGUI](https://tgui.eu/)
* [Box2D](https://box2d.org/) (optional for demo)
* [Boost](https://www.boost.org/users/download/) (optional for tests)

