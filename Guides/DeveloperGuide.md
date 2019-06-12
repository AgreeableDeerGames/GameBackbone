# GB Developer Guide

- [GB Developer Guide](#gb-developer-guide)
  - [1: Coding Guidelines](#1-coding-guidelines)
  - [2: IDE Setup](#2-ide-setup)
    - [2.1: Visual Studio](#21-visual-studio)
      - [2.1.1: Download C++](#211-download-c)
      - [2.1.2: Download Extensions (optional)](#212-download-extensions-optional)
      - [2.1.3: CMake Settings](#213-cmake-settings)
    - [2.2: Visual Studio Code](#22-visual-studio-code)
      - [2.2.1: Download Extensions](#221-download-extensions)
      - [2.2.2: CMake Settings](#222-cmake-settings)
      - [2.2.3: Set Working Directory](#223-set-working-directory)
      - [2.2.4: Set Environment (Linux Only)](#224-set-environment-linux-only)
  - [3: Running Tests](#3-running-tests)
    - [3.1: Visual Studio](#31-visual-studio)
    - [3.2: Visual Studio Code](#32-visual-studio-code)
  - [4: Productivity Assistants](#4-productivity-assistants)
  - [5: Recommended CMake Options](#5-recommended-cmake-options)
    - [5.1: Universal developer options](#51-universal-developer-options)
    - [5.2: vcpkg dependencies](#52-vcpkg-dependencies)
    - [5.3: Custom installed dependencies](#53-custom-installed-dependencies)

***

## 1: Coding Guidelines

See [style guide](https://github.com/lavinrp/GameBackbone/blob/master/Guides/StyleGuide.txt)

***

## 2: IDE Setup
### 2.1: Visual Studio
* [Download](https://visualstudio.microsoft.com/downloads/) Visual Studio 2017

#### 2.1.1: Download C++
Download the MSVC 14.1 toolset through the visual studio installer

#### 2.1.2: Download Extensions (optional) 
It is recommended that you download the following additions to visual studio
* [Download](https://marketplace.visualstudio.com/items?itemName=sergeb.GhostDoc) GhostDoc
* [Download](https://marketplace.visualstudio.com/items?itemName=VisualCPPTeam.TestAdapterforBoostTest) Test Adapter for Boost.Test
* [Download](https://marketplace.visualstudio.com/items?itemName=OpenCppCoverage.OpenCppCoveragePlugin) OpenCppCoverage

#### 2.1.3: CMake Settings
For every build configuration in CMakeSettings.json add a "cmakeCommandArgs" property.
The value of this property should be the cmake command line arguments required to set the set the variables from the [Recommended CMake Options](#5-recommended-cmake-options).

Sample:

    "cmakeCommandArgs": "-DCMAKE_TOOLCHAIN_FILE=C:\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake -DUSE_VCPKG_BOX2D=ON -DCMAKE_INSTALL_PREFIX=C:\\Some\\Temp\\install\\dir -DGAMEBACKBONE_BUILD_TESTS=ON -DGAMEBACKBONE_BUILD_DEMO=ON",
    

### 2.2: Visual Studio Code
* [Download](https://code.visualstudio.com/) Visual Studio Code

#### 2.2.1: Download Extensions
Download the following extensions
* [cpp tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) from microsoft
* [CMake Tools](https://marketplace.visualstudio.com/items?itemName=vector-of-bool.cmake-tools) from vector-of-bool

#### 2.2.2: CMake Settings
Add "cmake.configureSettings": {} to your settings.json
For every CMake option you want to set you should add another property to cmake.configureSettings. The properties follow the pattern "key":"value" where key is the CMake option that you want to set (without the -D) and value is the new value for the option. create a property for each of the [Recommended CMake Options](#5-recommended-cmake-options).


#### 2.2.3: Set Working Directory

Create a debug profile for the GameBackbone demo and/or unit tests by pointing the "Program" variable in launch.json to the respective executable file.
Set the current working directory of this profile to the folder where the executable files were generated.

#### 2.2.4: Set Environment (Linux Only)

If you are on **linux** you must set your environment to load the correct .so files at runtime. 

Do this by setting the environment variable in your debug configuration to:

    "environment": 
    [
	    {
	        "name": "LD_LIBRARY_PATH",
	        "value": "path/to/SFML/lib:path/to/TGUI/lib"
	    }
    ],

***
## 3: Running Tests
Tests should be run before every push. No branch will be merged into develop if any new tests are failing.

### 3.1: Visual Studio
Your options for running the unit tests from visual studio are:
* Download the boost test adapter and run the tests from there
* Run the tests by launching the test project
* Open a developer command prompt in the bin folder for the solution and launch the test executable from the command prompt
* Run tests through CTest
### 3.2: Visual Studio Code
* Run CTest or run tests through the terminal
***
## 4: Productivity Assistants
It is recommended that you download the following 3rd party apps
* [CppCheck](http://cppcheck.sourceforge.net/)
  - Standalone app that does a better job than the visual studio plugin of the same name
  - Required to use the visual studio plugin of the same name
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/index.html)
  - Used to build documentation that is output [here](https://lavinrp.github.io/GameBackbone/)

***
## 5: Recommended CMake Options

### 5.1: Universal developer options

|CMake variable|value|
|:---|:---|
|GAMEBACKBONE_BUILD_TESTS|ON|
|GAMEBACKBONE_BUILD_DEMO|ON|
|GAMEBACKBONE_RUN_CLANG_TIDY|ON|

### 5.2: vcpkg dependencies

|CMake variable|value|
|:---|:---|
|CMAKE_TOOLCHAIN_FILE|/vcpkg/scripts/buildsystems/vcpkg.cmake|
|USE_VCPKG_BOX2D|ON|

### 5.3: Custom installed dependencies

|CMake variable|value|
|:---|:---|
|BOOST_ROOT|/path/to/boost/install|
|SFML_DIR|/path/to/sfml/lib/cmake/SFML|
|TGUI_DIR|/path/to/tgui/lib/cmake/TGUI|
|BOX2D_DIR|/path/to/box2d/install|
|CMAKE_INSTALL_PREFIX|/path/to/some/temp/install/dir|

***