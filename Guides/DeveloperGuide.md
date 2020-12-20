# GB Developer Guide

- [GB Developer Guide](#gb-developer-guide)
  - [1: Coding Guidelines](#1-coding-guidelines)
  - [2: Dependencies](#2-dependencies)
  - [3: IDE Setup](#3-ide-setup)
    - [3.1: Visual Studio](#31-visual-studio)
      - [3.1.1: Download C++](#311-download-c)
      - [3.1.2: Download Extensions (optional)](#312-download-extensions-optional)
      - [3.1.3: CMake Settings](#313-cmake-settings)
    - [3.2: Visual Studio Code](#32-visual-studio-code)
      - [3.2.1: Download Extensions](#321-download-extensions)
      - [3.2.2: CMake Settings](#322-cmake-settings)
      - [3.2.3: Set Working Directory](#323-set-working-directory)
      - [3.2.4: Set Environment (Linux Only)](#324-set-environment-linux-only)
  - [4: Running Tests](#4-running-tests)
    - [4.1: Visual Studio](#41-visual-studio)
    - [4.2: Visual Studio Code](#42-visual-studio-code)
  - [5: Misc Tools](#5-misc-tools)
  - [6: Recommended CMake Options](#6-recommended-cmake-options)
    - [6.1: Universal developer options](#61-universal-developer-options)
    - [6.2: vcpkg dependencies](#62-vcpkg-dependencies)
    - [6.3: Custom installed dependencies](#63-custom-installed-dependencies)

***

## 1: Coding Guidelines

See [style guide](https://github.com/AgreeableDeerGames/GameBackbone/blob/master/Guides/StyleGuide.txt)

***
## 2: Dependencies
* Follow the [dependencies section](https://github.com/AgreeableDeerGames/GameBackbone/blob/master/Guides/InstallGuide.md#22-install-dependencies) of the install guide.
* Note that you must have your build environment set up for this to work. On windows this will require installing VisualStudio.

## 3: IDE Setup
### 3.1: Visual Studio
* [Download](https://visualstudio.microsoft.com/downloads/) Visual Studio 2019

#### 3.1.1: Download C++
Download the latest C++ toolset through the visual studio installer

#### 3.1.2: Download Extensions (optional) 
It is recommended that you download the following additions to visual studio
* [Download](https://marketplace.visualstudio.com/items?itemName=VisualCPPTeam.TestAdapterforBoostTest) Test Adapter for Boost.Test
* [Download](https://marketplace.visualstudio.com/items?itemName=OpenCppCoverage.OpenCppCoveragePlugin) OpenCppCoverage

#### 3.1.3: CMake Settings
Go to `project` menu then select `CMake Settings for GameBackboneProject`. Set the variables from the [Recommended CMake Options](#5-recommended-cmake-options).

Note that if you are using VCPKG you should set the `CMake toolchain file` to the `vcpkg.cmake` file found in your vcpkg install under `scripts/buildsystems`.

### 3.2: Visual Studio Code
* [Download](https://code.visualstudio.com/) Visual Studio Code

#### 3.2.1: Download Extensions
Download the following extensions
* [cpp tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) from microsoft
* [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) from microsoft

#### 3.2.2: CMake Settings
Add "cmake.configureSettings": {} to your settings.json
For every CMake option you want to set you should add another property to cmake.configureSettings. The properties follow the pattern "key":"value" where key is the CMake option that you want to set (without the -D) and value is the new value for the option. create a property for each of the [Recommended CMake Options](#6-recommended-cmake-options).


#### 3.2.3: Set Working Directory

Create a debug profile for the GameBackbone demo and/or unit tests by pointing the "Program" variable in launch.json to the respective executable file.
Set the current working directory of this profile to the folder where the executable files were generated.

#### 3.2.4: Set Environment (Linux Only)

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
## 4: Running Tests

Tests are automatically run by the GB CI on every push. If all tests pass a green checkmark will be displayed next to the branch name on GitHub. No branch will be merged into develop if any new tests are failing.


### 4.1: Visual Studio
Your options for running the unit tests from Visual Studio are:
* Download the boost test adapter and run the tests from there
* Run the tests by launching the test project
* Open a developer command prompt in the bin folder for the solution and launch the test executable from the command prompt
* Run tests through CTest
### 4.2: Visual Studio Code
Your options for running the unit tests from Visual Studio Code are:
* Run CTest
* Run tests through the terminal
***
## 5: Misc Tools
It is recommended that you download the following 3rd party apps
* [CppCheck](http://cppcheck.sourceforge.net/)
  - The Standalone app does a better job than the visual studio plugin of the same name
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/index.html)
  - Used to build documentation that is output [here](https://AgreeableDeerGames.github.io/GameBackbone/)

***
## 6: Recommended CMake Options

### 6.1: Universal developer options

|CMake variable|value|
|:---|:---|
|GAMEBACKBONE_BUILD_TESTS|ON|
|GAMEBACKBONE_BUILD_DEMO|ON|
|GAMEBACKBONE_RUN_CLANG_TIDY|ON|

### 6.2: vcpkg dependencies

|CMake variable|value|
|:---|:---|
|CMAKE_TOOLCHAIN_FILE|/vcpkg/scripts/buildsystems/vcpkg.cmake|
|USE_VCPKG_BOX2D|OFF|

### 6.3: Custom installed dependencies

|CMake variable|value|
|:---|:---|
|BOOST_ROOT|/path/to/boost/install|
|SFML_DIR|/path/to/sfml/lib/cmake/SFML|
|TGUI_DIR|/path/to/tgui/lib/cmake/TGUI|
|BOX2D_DIR|/path/to/box2d/install|
|CMAKE_INSTALL_PREFIX|/path/to/some/temp/install/dir|

***